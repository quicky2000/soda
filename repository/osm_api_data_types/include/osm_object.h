/*
    This file is part of osm_api_data_types, C++ representation of Openstreetmap
    API 0.6 primitive objects
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
#ifndef _OSM_OBJECT_H_
#define _OSM_OBJECT_H_

#include "quicky_exception.h"
#include <string>
#include <map>
#include <cassert>
#include <inttypes.h>
#include <iostream>
#include <sstream>

namespace osm_api_data_types
{
  class osm_object
  {
    friend std::ostream & operator<<(std::ostream & p_stream,const osm_object & p_object);
  public:
    typedef uint64_t t_osm_id;

    // Constructor
    inline osm_object(const t_osm_id  & p_id,
		      const t_osm_id & p_user_id,
		      const std::string & p_user);

    // Attributes getter
    inline const t_osm_id & get_id(void)const;
    inline const t_osm_id & get_user_id(void)const;
    inline const std::string & get_user(void)const;
    
    // Tags operations
    inline void add_tag(const std::string & p_name, const std::string & p_value);
    inline void remove_tag(const std::string & p_name);
    inline const std::string & get_tag_value(const std::string & p_name)const;
    inline void modify_tag_value(const std::string & p_name,const std::string & p_value);
    inline bool contains_tag(const std::string & p_name)const;
    inline const std::map<std::string,std::string> & get_tags(void)const;

    // Utility
    inline void tags_to_string(std::string & p_string)const;
  private:
    t_osm_id m_id;
    t_osm_id m_user_id;
    std::string m_user;
    std::map<std::string,std::string> m_tags;

  };

  //------------------------------------------------------------------------------
  inline std::ostream & operator<<(std::ostream & p_stream,const osm_object & p_object)
    {
      p_stream << "user_id=" << p_object.m_user_id << " user=" << p_object.m_user ;
      return p_stream;
    }
  // Constructor
  //----------------------------------------------------------------------------
  osm_object::osm_object(const t_osm_id  & p_id,
			 const osm_object::t_osm_id & p_user_id,
			 const std::string & p_user):
    m_id(p_id),
    m_user_id(p_user_id),
    m_user(p_user)
      {
      }

    // Attributes getter
    //----------------------------------------------------------------------------
    const osm_object::t_osm_id & osm_object::get_id(void)const
      {
	return m_id;
      }

    //----------------------------------------------------------------------------
    const osm_object::t_osm_id & osm_object::get_user_id(void)const
      {
	return m_user_id;
      }
    //----------------------------------------------------------------------------
    const std::string & osm_object::get_user(void)const
      {
	return m_user;
      }
    
    // Tags operations
    //----------------------------------------------------------------------------
    void osm_object::add_tag(const std::string & p_name, const std::string & p_value)
    {
      std::map<std::string,std::string>::const_iterator l_iter = m_tags.find(p_name);
      if(l_iter != m_tags.end())
        {
          std::cout << "WARNING : there is already a tag with name \"" << p_name << "\". It can be due to bad minute diff formatting" << std::endl ;
        }
      m_tags.insert(make_pair(p_name,p_value));
    }
    //----------------------------------------------------------------------------
    void osm_object::remove_tag(const std::string & p_name)
    {
      std::map<std::string,std::string>::iterator l_iter = m_tags.find(p_name);
      if(m_tags.end() == l_iter)
	{
	  std::stringstream l_stream;
	  l_stream << "ERROR : you try to remove tag \"" << p_name << "\" which doesn't exist";
	  throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	}
      m_tags.erase(l_iter);
    }
    //----------------------------------------------------------------------------
    const std::string & osm_object::get_tag_value(const std::string & p_name)const
      {
	std::map<std::string,std::string>::const_iterator l_iter = m_tags.find(p_name);
	if(m_tags.end() == l_iter)
	  {
	    std::stringstream l_stream;
	    l_stream << "ERROR : you try to get value of tag \"" << p_name << "\" which doesn't exist";
	  throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	  }
	return l_iter->second;
      }
    //----------------------------------------------------------------------------
    void osm_object::modify_tag_value(const std::string & p_name,const std::string & p_value)
    {
      std::map<std::string,std::string>::iterator l_iter = m_tags.find(p_name);
      if(m_tags.end() == l_iter)
	{
	  std::stringstream l_stream;
	  l_stream << "ERROR : you try to modify value of tag \"" << p_name << "\" which doesn't exist";
	  throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	  }
      l_iter->second = p_value;
    }

    //----------------------------------------------------------------------------
    bool osm_object::contains_tag(const std::string & p_name)const
    {
      std::map<std::string,std::string>::const_iterator l_iter = m_tags.find(p_name);
      return(l_iter != m_tags.end());      
    }

    //----------------------------------------------------------------------------
    const std::map<std::string,std::string> & osm_object::get_tags(void)const
      {
        return m_tags;
      }
    //----------------------------------------------------------------------------
    void osm_object::tags_to_string(std::string & p_string)const
    {
      for(std::map<std::string,std::string>::const_iterator l_iter = m_tags.begin();
            l_iter != m_tags.end();
            ++l_iter)
        {
          p_string += "  " + l_iter->first + "=" + l_iter->second + "\n" ;
        }
    }

}

#endif // _OSM_OBJECT_H_
