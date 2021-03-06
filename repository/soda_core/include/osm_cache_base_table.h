/*
    This file is part of osm_diff_watcher, Openstreetmap diff analyze framework
    The aim of this software is to provided generic facilities for diff analyzis
    to allow developers to concentrate on analyze rather than diff management 
    infrastructure
    Copyright (C) 2012  Julien Thevenon ( julien_thevenon at yahoo.fr )

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef _OSM_CACHE_BASE_TABLE_H
#define _OSM_CACHE_BASE_TABLE_H

#include "osm_cache_base_table_description.h"
#include "osm_api_data_types.h"
#include "my_sqlite3.h"
#include "quicky_exception.h"
#include <inttypes.h>
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <sstream>
#include <vector>

namespace osm_diff_watcher
{
  class named_item;

  template <class T>
    class osm_cache_base_table
    {
    public:
      void create(T & p_named_item);
      void force_create(const T & p_named_item);
      void update(const T & p_named_item);
      void remove(const T & p_named_item);
      uint32_t get(const osm_api_data_types::osm_object::t_osm_id & p_id, T & p_data);
      void get_all(std::vector<T> & p_list);

      osm_cache_base_table(const std::string & p_name=osm_cache_base_table_description<T>::get_class_type());
      ~osm_cache_base_table(void);
      const std::string & get_name(void)const;
    protected:
      void set_db(sqlite3 *p_db,bool p_primary_key_id=true);
      sqlite3 * get_db(void);

    private:
      osm_api_data_types::osm_object::t_osm_id get_max_id(void);
      const std::string m_name;
      sqlite3 *m_db;
      sqlite3_stmt *m_create_stmt;
      sqlite3_stmt *m_update_stmt;
      sqlite3_stmt *m_delete_stmt;
      sqlite3_stmt *m_get_by_id_stmt;
      sqlite3_stmt *m_get_all_stmt;
      sqlite3_stmt *m_get_max_id_stmt;
    };


  //------------------------------------------------------------------------------
  template <class T>
    osm_cache_base_table<T>::osm_cache_base_table(const std::string & p_name):
    m_name(p_name),
    m_db(NULL),
    m_create_stmt(NULL),
    m_update_stmt(NULL),
    m_delete_stmt(NULL),
    m_get_by_id_stmt(NULL),
    m_get_all_stmt(NULL),
    m_get_max_id_stmt(NULL)
      {
      }

    //------------------------------------------------------------------------------
    template <class T>
      osm_cache_base_table<T>::~osm_cache_base_table(void)
      {
	sqlite3_finalize(m_get_max_id_stmt);
	sqlite3_finalize(m_get_all_stmt);
	sqlite3_finalize(m_get_by_id_stmt);
	sqlite3_finalize(m_delete_stmt);  
	sqlite3_finalize(m_update_stmt);  
	sqlite3_finalize(m_create_stmt);  
#ifdef DEBUG
	std::cout << "Table " << m_name << " end of destruction" << std::endl ;
#endif
      }

    //------------------------------------------------------------------------------
    template <class T>
      const std::string & osm_cache_base_table<T>::get_name(void)const
      {
        return m_name;
      }
    
    //------------------------------------------------------------------------------
    template <class T>
      sqlite3 * osm_cache_base_table<T>::get_db(void)
      {
	return m_db;
      }

    //------------------------------------------------------------------------------
    template <class T>
      void osm_cache_base_table<T>::set_db(sqlite3 *p_db,bool p_primary_key_id)
      {
        if(NULL == p_db) throw quicky_exception::quicky_logic_exception("p_db should not be NULL",__LINE__,__FILE__);
	m_db = p_db;

	sqlite3_stmt *l_stmt = NULL;

	// Creation of table
	//--------------------
	int l_status = sqlite3_prepare_v2(m_db,("CREATE TABLE IF NOT EXISTS " + m_name + " ( Id INTEGER" + (p_primary_key_id ? " PRIMARY KEY AUTOINCREMENT": "")+", "+ osm_cache_base_table_description<T>::get_table_fields_declaration()+");").c_str(),-1,&l_stmt,NULL);
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during preparation of statement to create " << m_name << " table : " << sqlite3_errmsg(m_db) ;
	    throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	  }
  
	l_status = sqlite3_step(l_stmt);
	if(!l_status == SQLITE_DONE)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during creation of " << m_name << " table : " << sqlite3_errmsg(m_db) ;
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }
	sqlite3_finalize(l_stmt);  

	// Preparing named_item create statement
	//----------------------------------------
	l_status = sqlite3_prepare_v2(m_db,("INSERT INTO " + m_name + " (Id,"+osm_cache_base_table_description<T>::get_table_fields()+") VALUES ($id, "+osm_cache_base_table_description<T>::get_field_values()+")").c_str(),-1,&m_create_stmt,NULL);
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during preparation of statement to create " << m_name << " item : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	  }

	// Preparing named_item update statement
	//-------------------------------------------
	l_status = sqlite3_prepare_v2(m_db,("UPDATE " + m_name + " SET " + osm_cache_base_table_description<T>::get_update_fields() + " WHERE Id == $id ;").c_str(),-1,&m_update_stmt,NULL);
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during preparation of statement to update " << m_name << " item : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	  }

	// Preparing named_item delete statements
	//--------------------------------------------
	l_status = sqlite3_prepare_v2(m_db,("DELETE FROM " + m_name + " WHERE Id == $id").c_str(),-1,&m_delete_stmt,NULL);
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during preparation of statement to delete " << m_name << " item : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	  }

	// Preparing named_item get_by_id statements
	//--------------------------------------------
	l_status = sqlite3_prepare_v2(m_db,("SELECT Id,"+osm_cache_base_table_description<T>::get_table_fields()+" FROM " + m_name + " WHERE Id == $id").c_str(),-1,&m_get_by_id_stmt,NULL);
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during preparation of statement to get " << m_name << " item by id: " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	  }

	// Preparing get_all statements
	//--------------------------------------------
	l_status = sqlite3_prepare_v2(m_db,("SELECT Id,"+osm_cache_base_table_description<T>::get_table_fields()+" FROM " + m_name).c_str(),-1,&m_get_all_stmt,NULL);
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during preparation of statement to get all " << m_name << " items : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	  }

	// Preparing get_max_id statements
	//--------------------------------------------
	l_status = sqlite3_prepare_v2(m_db,("SELECT MAX(Id) FROM " + m_name).c_str(),-1,&m_get_max_id_stmt,NULL);
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during preparation of statement to get max Id of " << m_name << " table : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	  }

#ifdef ENABLE_SUCCESS_STATUS_DISPLAY
	std::cout << "Statements OK" << std::endl ;

	std::cout << "Table " << m_name << " successfully created" << std::endl ;
#endif  
      }

    //------------------------------------------------------------------------------
    template <class T>
      void osm_cache_base_table<T>::create(T & p_named_item)
      {
	// Determine Id if needed
	if(!p_named_item.get_id())
	  {
	    osm_api_data_types::osm_object::t_osm_id l_new_id = get_max_id() + 1;
	    p_named_item.set_id(l_new_id);
	  }
	force_create(p_named_item);

      }
    //------------------------------------------------------------------------------
    template <class T>
      void osm_cache_base_table<T>::force_create(const T & p_named_item)
      {
        if(!p_named_item.get_id()) throw quicky_exception::quicky_logic_exception("Trying to create an object with id 0",__LINE__,__FILE__);

	// Binding values to statement
	//----------------------------
	int l_status = sqlite3_bind_int64(m_create_stmt,sqlite3_bind_parameter_index(m_create_stmt,"$id"),p_named_item.get_id());
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during binding of Id parameter for create statement of " << m_name << " : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	  }
  
	osm_cache_base_table_description<T>::bind_item_values(p_named_item,m_create_stmt,m_db);

	// Executing statement
	//---------------------
	l_status = sqlite3_step(m_create_stmt);
	if( l_status == SQLITE_DONE)
	  {
#ifdef ENABLE_SUCCESS_STATUS_DISPLAY
	    std::cout << m_name << " successfully created" << std::endl ;
#endif
	  }
	else
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during creation of " << m_name << " item : " << sqlite3_errmsg(m_db) ;
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }

	// Reset the statement for the next use
	//--------------------------------------
	l_status = sqlite3_reset(m_create_stmt);  
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during reset of " << m_name << " create statement : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }

	// Reset bindings because they are now useless
	//--------------------------------------------
	l_status = sqlite3_clear_bindings(m_create_stmt);
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during reset of bindings of " << m_name << " create statement : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }

      }
    //------------------------------------------------------------------------------
    template <class T>
      void osm_cache_base_table<T>::update(const T & p_named_item)
      {
	// Binding values to statement
	//----------------------------
	int l_status = sqlite3_bind_int64(m_update_stmt,sqlite3_bind_parameter_index(m_update_stmt,"$id"),p_named_item.get_id());
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during binding of Id parameter for update statement of " << m_name << " : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	  }
  
	osm_cache_base_table_description<T>::bind_item_values(p_named_item,m_update_stmt,m_db);

	// Executing statement
	//---------------------
	l_status = sqlite3_step(m_update_stmt);
	if( l_status == SQLITE_DONE)
	  {
#ifdef ENABLE_SUCCESS_STATUS_DISPLAY
	    std::cout << m_name << " successfully updated" << std::endl ;
#endif
	  }
	else
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during update of " << m_name << " : " << sqlite3_errmsg(m_db) ;
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }

	// Reset the statement for the next use
	//--------------------------------------
	l_status = sqlite3_reset(m_update_stmt);  
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during reset of " << m_name << " update statement : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }

	// Reset bindings because they are now useless
	//--------------------------------------------
	l_status = sqlite3_clear_bindings(m_update_stmt);
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during reset of bindings of " << m_name << " update statement : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }


      }
    //------------------------------------------------------------------------------
    template <class T>
      void osm_cache_base_table<T>::remove(const T & p_named_item)
      {
	// Binding values to statement
	//----------------------------
	int l_status = sqlite3_bind_int64(m_delete_stmt,sqlite3_bind_parameter_index(m_delete_stmt,"$id"),p_named_item.get_id());
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during binding of Id parameter for delete statement of " << m_name << " : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	  }
    
	// Executing statement
	//---------------------
	l_status = sqlite3_step(m_delete_stmt);
	if( l_status == SQLITE_DONE)
	  {
#ifdef ENABLE_SUCCESS_STATUS_DISPLAY
	    std::cout << m_name << " successfully deleted" << std::endl ;
#endif
	  }
	else
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during delete of " << m_name << " : " << sqlite3_errmsg(m_db) ;
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }

	// Reset the statement for the next use
	//--------------------------------------
	l_status = sqlite3_reset(m_delete_stmt);  
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during reset of " << m_name << " delete statement : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }

	// Reset bindings because they are now useless
	//--------------------------------------------
	l_status = sqlite3_clear_bindings(m_delete_stmt);
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during reset of bindings of " << m_name << " delete statement : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }

      }
    //------------------------------------------------------------------------------
    template <class T>
      uint32_t osm_cache_base_table<T>::get(const osm_api_data_types::osm_object::t_osm_id & p_id, T & p_data)
      {
  
	uint32_t l_result = 0;

	// Binding values to statement
	//----------------------------
	int l_status = sqlite3_bind_int64(m_get_by_id_stmt,sqlite3_bind_parameter_index(m_get_by_id_stmt,"$id"),p_id);
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during binding of Id parameter for get_by_id statement of " << m_name << " : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	  }
    
	// Executing statement
	//---------------------
	l_status = sqlite3_step(m_get_by_id_stmt);
	if( l_status == SQLITE_ROW)
	  {
#ifdef ENABLE_SUCCESS_STATUS_DISPLAY
	    std::cout << m_name << " successfully selected" << std::endl ;
#endif
	    p_data = osm_cache_base_table_description<T>::get_item_from_row(m_get_by_id_stmt);

	    // Ensure that ID is unique
	    l_status = sqlite3_step(m_get_by_id_stmt);
	    if( l_status == SQLITE_DONE)
	      {
#ifdef ENABLE_SUCCESS_STATUS_DISPLAY
		std::cout << m_name << " successfully selected done" << std::endl ;
#endif
		l_result = 1;
	      }
	    else
	      {
                std::stringstream l_stream;
                l_stream << "ERROR during selection of " << m_name << " : Id " << p_id << " is not unique " << sqlite3_errmsg(m_db) ;
		throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	      }
	  }
	else if(l_status != SQLITE_DONE)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during selection of " << m_name << " : " << sqlite3_errmsg(m_db) ;
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }



	// Reset the statement for the next use
	//--------------------------------------
	l_status = sqlite3_reset(m_get_by_id_stmt);  
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during reset of " << m_name << " get_by_id statement : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }

	// Reset bindings because they are now useless
	//--------------------------------------------
	l_status = sqlite3_clear_bindings(m_get_by_id_stmt);
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during reset of bindings of " << m_name << " get_by_id statement : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }
	return l_result;
      }
    //------------------------------------------------------------------------------
    template <class T>
      void osm_cache_base_table<T>::get_all(std::vector<T> & p_list)
      {

	int l_status = 0;
	// Executing statement
	//---------------------
	while( (l_status = sqlite3_step(m_get_all_stmt)) == SQLITE_ROW)
	  {
	    p_list.push_back(osm_cache_base_table_description<T>::get_item_from_row(m_get_all_stmt));
	  }
	if(l_status != SQLITE_DONE)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during selection of " << m_name << " : " << sqlite3_errmsg(m_db) ;
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }

#ifdef ENABLE_SUCCESS_STATUS_DISPLAY
	std::cout <<  m_name << " successfully listed" << std::endl ;
#endif

	// Reset the statement for the next use
	//--------------------------------------
	l_status = sqlite3_reset(m_get_all_stmt);  
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during reset of " << m_name << " get_all statement : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }

      }

    //------------------------------------------------------------------------------
    template <class T>
      osm_api_data_types::osm_object::t_osm_id osm_cache_base_table<T>::get_max_id(void)
      {
	int l_status = 0;
	osm_api_data_types::osm_object::t_osm_id l_result = 0;

	// Executing statement
	//---------------------
	l_status = sqlite3_step(m_get_max_id_stmt);
	if( l_status == SQLITE_ROW)
	  {
#ifdef ENABLE_SUCCESS_STATUS_DISPLAY
	    std::cout << m_name << " successfully max determined" << std::endl ;
#endif
	    l_result = sqlite3_column_int64(m_get_max_id_stmt,0);

	    // Ensure that ID is unique
	    l_status = sqlite3_step(m_get_max_id_stmt);
	    if( l_status == SQLITE_DONE)
	      {
#ifdef ENABLE_SUCCESS_STATUS_DISPLAY
		std::cout << m_name << " successfully max done" << std::endl ;
#endif
	      }
	    else
	      {
                std::stringstream l_stream;
                l_stream << "ERROR during determination of max Id of " << m_name << " table : " << sqlite3_errmsg(m_db) ;
		throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	      }
	  }
	else
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during determination of max Id of " << m_name << " : " << sqlite3_errmsg(m_db) ;
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }



	// Reset the statement for the next use
	//--------------------------------------
	l_status = sqlite3_reset(m_get_max_id_stmt);  
	if(l_status != SQLITE_OK)
	  {
            std::stringstream l_stream;
            l_stream << "ERROR during reset of " << m_name << " get_max_id statement : " << sqlite3_errmsg(m_db) ;     
	    throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
	  }

	return l_result;
      }

}

#endif // _OSM_CACHE_BASE_TABLE_H
//EOF
