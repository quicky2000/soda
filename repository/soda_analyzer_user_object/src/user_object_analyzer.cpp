/*
  This file is part of osm_diff_analyzer_user_object, Openstreetmap
  diff analyzer based on CPP diff representation. It's aim is to survey
  objects edited by parametered used and to generate an alert in case of 
  edition on these objects
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
#include "user_object_analyzer.h"
#include "user_object_common_api.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cassert>

namespace osm_diff_analyzer_user_object
{
  //------------------------------------------------------------------------------
  user_object_analyzer::user_object_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf,
					     user_object_common_api & p_api):
    osm_diff_analyzer_cpp_if::cpp_analyzer_base("user_analyser",p_conf->get_name(),""),
    m_api(p_api),
    m_done(false),
    m_report(),
    m_user_name(""),
    m_db(get_name()+".sqlite3")
  {
    // Register module to be able to use User Interface
    m_api.ui_register_module(*this,get_name());

    std::ifstream l_old_file("user_object.sqlite3");
    if(l_old_file.is_open())
      {
        l_old_file.close();
	std::stringstream l_stream;
	l_stream << "ERROR : user_object.sqlite3 is now deprecated to allow multi-instance usage. Please rename it to " << (get_name()+".sqlite3");
	throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
      }

    const std::map<std::string,std::string> & l_conf_parameters = p_conf->get_parameters();

    // User_name parameter management
    std::map<std::string,std::string>::const_iterator l_iter = l_conf_parameters.find("user_name");
    if(l_iter == l_conf_parameters.end())
      {
	std::stringstream l_stream ;
	l_stream << "ERROR : missing mandatory \"user_name\" parameter in module \"" << get_name() <<"\"" ;
	throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
      }

    std::stringstream l_stream;
    l_stream << "parameter[\"user_name\"]=\"" << l_iter->second << "\"" << std::endl ;
    m_api.ui_append_log_text(*this,l_stream.str());

    m_user_name = l_iter->second;
    
    // init_file parameter management
    l_iter = l_conf_parameters.find("init_file");
    if(l_iter != l_conf_parameters.end())
      {
	std::string l_file_name = l_iter->second;
	std::string l_file_extension = l_file_name.substr(l_file_name.size()-4);
	{
	  std::stringstream l_stream;
	  l_stream << "Extension is \"" << l_file_extension << "\"" << std::endl ;
	  m_api.ui_append_log_text(*this,l_stream.str());
	}
	if(l_file_extension == ".osm")
	  {
	    std::vector<osm_api_data_types::osm_node*> l_nodes;
	    std::vector<osm_api_data_types::osm_way*> l_ways;
	    std::vector<osm_api_data_types::osm_relation*> l_relations;

	    std::set<osm_api_data_types::osm_object::t_osm_id> l_nodes_under_survey;
	    m_db.get_all_node_ids(l_nodes_under_survey);
	    std::set<osm_api_data_types::osm_object::t_osm_id> l_ways_under_survey;
	    m_db.get_all_way_ids(l_ways_under_survey);
	    std::set<osm_api_data_types::osm_object::t_osm_id> l_relations_under_survey;
	    m_db.get_all_relation_ids(l_relations_under_survey);

            std::set<osm_api_data_types::osm_node*> l_nodes_to_survey;
            std::set<osm_api_data_types::osm_way*> l_ways_to_survey;
            std::set<osm_api_data_types::osm_relation*> l_relations_to_survey;

            m_api.ui_append_log_text(*this,"Parse OSM file");
	    m_api.get_osm_file_content(l_file_name,
				       l_nodes,
				       l_ways,
				       l_relations);

            m_api.ui_append_log_text(*this,"Check if objects are already under survey");
	    uint32_t l_nb_added_nodes= 0;
	    uint32_t l_nb_added_ways= 0;
	    uint32_t l_nb_added_relations= 0;
	    for(std::vector<osm_api_data_types::osm_node*>::const_iterator l_iter = l_nodes.begin();
		l_iter != l_nodes.end();
		++l_iter)
	      {
		if(l_nodes_under_survey.find((*l_iter)->get_id()) == l_nodes_under_survey.end()/* && !m_db.contains(*l_iter)*/)
		  {
                    l_nodes_to_survey.insert(*l_iter);
		    l_nodes_under_survey.insert((*l_iter)->get_id());
                    //		    m_db.insert(*l_iter);
                    //  m_api.cache(**l_iter);
		    ++l_nb_added_nodes;
		  }
	      }
	    for(std::vector<osm_api_data_types::osm_way*>::const_iterator l_iter = l_ways.begin();
		l_iter != l_ways.end();
		++l_iter)
	      {
		if(l_ways_under_survey.find((*l_iter)->get_id()) == l_ways_under_survey.end() /*&& !m_db.contains(*l_iter)*/)
		  {
                    l_ways_to_survey.insert(*l_iter);
		    l_ways_under_survey.insert((*l_iter)->get_id());
                    //  m_db.insert(*l_iter);
                    // m_api.cache(**l_iter);
		    ++l_nb_added_ways;
		  }
	      }
	    for(std::vector<osm_api_data_types::osm_relation*>::const_iterator l_iter = l_relations.begin();
		l_iter != l_relations.end();
		++l_iter)
	      {
		if(l_relations_under_survey.find((*l_iter)->get_id()) == l_relations_under_survey.end() /*&& !m_db.contains(*l_iter)*/)
		  {
                    l_relations_to_survey.insert(*l_iter);
		    l_relations_under_survey.insert((*l_iter)->get_id());
                    //   m_db.insert(*l_iter);
                    //  m_api.cache(**l_iter);
		    ++l_nb_added_relations;
		  }
	      }

            m_api.ui_append_log_text(*this,"Survey objects that are not already under survey");            
            // Insertion in database
            for(std::set<osm_api_data_types::osm_node*>::const_iterator l_iter = l_nodes_to_survey.begin();
                l_iter != l_nodes_to_survey.end();
                ++l_iter)
              {

		m_db.insert(**l_iter);
		m_api.cache(**l_iter);                
              }
            
            for(std::set<osm_api_data_types::osm_way*>::const_iterator l_iter = l_ways_to_survey.begin();
                l_iter != l_ways_to_survey.end();
                ++l_iter)
              {
		m_db.insert(**l_iter);
		m_api.cache(**l_iter);                
              }
            
            for(std::set<osm_api_data_types::osm_relation*>::const_iterator l_iter = l_relations_to_survey.begin();
                l_iter != l_relations_to_survey.end();
                ++l_iter)
              {
		m_db.insert(**l_iter);
		m_api.cache(**l_iter);                
              }

	    //Free memory
	    m_api.ui_append_log_text(*this,"Memory clean");
	    for(std::vector<osm_api_data_types::osm_node*>::const_iterator l_iter = l_nodes.begin();
		l_iter != l_nodes.end();
		++l_iter)
	      {
		delete *l_iter;
	      }
	    for(std::vector<osm_api_data_types::osm_way*>::const_iterator l_iter = l_ways.begin();
		l_iter != l_ways.end();
		++l_iter)
	      {
		delete *l_iter;
	      }
	    for(std::vector<osm_api_data_types::osm_relation*>::const_iterator l_iter = l_relations.begin();
		l_iter != l_relations.end();
		++l_iter)
	      {
		delete *l_iter;
	      }
	    {
	      {
		std::stringstream l_stream;
		l_stream << l_nb_added_nodes << " nodes put under survey" ;
		m_api.ui_append_log_text(*this,l_stream.str());
	      }
	      {
		std::stringstream l_stream;
		l_stream << l_nb_added_ways << " ways put under survey" ;
		m_api.ui_append_log_text(*this,l_stream.str());
	      }
	      {
		std::stringstream l_stream;
		l_stream << l_nb_added_relations << " relations put under survey" ;
		m_api.ui_append_log_text(*this,l_stream.str());
	      }
	    }
	  }
	else if(l_file_extension == ".osc")
	  {
	    const std::vector<osm_api_data_types::osm_change*> * const l_changes = m_api.get_osm_change_file_content(l_file_name);
	    
	    analyze(*l_changes);

	    // Deletion of C++ representation of file content
	    for(std::vector<osm_api_data_types::osm_change*>::const_iterator l_iter = l_changes->begin();
		l_iter != l_changes->end();
		++l_iter)
	      {
		delete *l_iter;
	      }
	    delete l_changes;

	  }
	else
	  {
	    std::stringstream l_atream;
	    l_stream << "WARNING : Unknown extension \"" << l_file_extension << "\" ( should be .som or .osc ) ignoring file \"" << l_file_name << "\"" ;
	    m_api.ui_append_log_text(*this,l_stream.str());
	  }
      }

  }

  //------------------------------------------------------------------------------
  void user_object_analyzer::create_report(void)
  {
    std::string l_report_file_name = m_user_name+"_object_report";
    std::string l_complete_report_file_name = l_report_file_name + ".html";
    std::ifstream l_test_file;
    uint32_t l_number = 0;
    bool l_continu = true;
    while(l_continu)
      {
        l_test_file.open(l_complete_report_file_name.c_str());
        l_continu = l_test_file.is_open();
        if(l_continu)
          {
            ++l_number;
            std::stringstream l_number_str;
            l_number_str << l_number;
            l_complete_report_file_name = l_report_file_name + "_" + l_number_str.str() + ".html";
            l_test_file.close();
          }
      }

    
    // Creating report
    m_report.open(l_complete_report_file_name.c_str());
    if(m_report.fail())
      {
	std::stringstream l_stream;
	l_stream << "ERROR : unabled to open \"" << l_complete_report_file_name << "\"" ;
	throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
      }
    m_report << "<html>" << std::endl ;
    m_report << "\t<head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" << std::endl ;
    m_report << "\t\t<title>" << m_user_name << " object report</title>" << std::endl ;
    m_report << "\t</head>" << std::endl ;
    m_report << "\t<body><H1>" << m_user_name << " object report</H1>" << std::endl ;

    m_api.ui_declare_html_report(*this,l_complete_report_file_name);
  }

  //------------------------------------------------------------------------------
  user_object_analyzer::~user_object_analyzer(void)
  {

    if(m_report.is_open())
      {
        m_report << "</body>" << std::endl ;
        m_report << "</html>" << std::endl ;
        
        m_report.close();
      }
  }

  //------------------------------------------------------------------------------
  void user_object_analyzer::init(const osm_diff_analyzer_if::osm_diff_state * p_diff_state)
  {
    std::stringstream l_stream;
    l_stream << "Starting analyze of diff " << p_diff_state->get_sequence_number() << std::endl ;
    m_api.ui_append_log_text(*this,l_stream.str());
  }

  //------------------------------------------------------------------------------
  void user_object_analyzer::analyze(const std::vector<osm_api_data_types::osm_change*> & p_changes)
  {
    uint32_t m_deletion = 0;
    uint32_t m_creation = 0;
    uint32_t m_modification = 0;

    for(std::vector<osm_api_data_types::osm_change*>::const_iterator l_iter = p_changes.begin();
        l_iter != p_changes.end();
        ++l_iter)
      {
        const osm_api_data_types::osm_core_element * const l_element = (*l_iter)->get_core_element();
        if(l_element == NULL) throw quicky_exception::quicky_logic_exception("Core element should not be NULL",__LINE__,__FILE__);

        switch(l_element->get_core_type())
          {
          case osm_api_data_types::osm_core_element::NODE :
	    generic_analyze<osm_api_data_types::osm_node>(*l_element,(*l_iter)->get_type());
            break;
          case osm_api_data_types::osm_core_element::WAY :
	    generic_analyze<osm_api_data_types::osm_way>(*l_element,(*l_iter)->get_type());
            break;
          case osm_api_data_types::osm_core_element::RELATION :
	    generic_analyze<osm_api_data_types::osm_relation>(*l_element,(*l_iter)->get_type());
            break;
          case osm_api_data_types::osm_core_element::INTERNAL_INVALID:
	    {
	      std::stringstream l_stream;
	      l_stream << "Unexpected core type value \"" << osm_api_data_types::osm_core_element::get_osm_type_str(l_element->get_core_type()) << "\"" ;
	      throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	    }
            break;
          }

        switch((*l_iter)->get_type())
          {
          case osm_api_data_types::osm_change::CREATION :
            ++m_creation;
            break;
          case osm_api_data_types::osm_change::MODIFICATION :
            ++m_modification;
            break;
          case osm_api_data_types::osm_change::DELETION :
            ++m_deletion;
            break;
          case osm_api_data_types::osm_change::INTERNAL_INVALID :
	    {
	      throw quicky_exception::quicky_logic_exception("Unexpected change type",__LINE__,__FILE__);
	    }
            break;
          }
      }
    {
      std::stringstream l_stream;
      l_stream << "--------------------------" << std::endl ;
      l_stream << "Creation : " << m_creation << std::endl ;
      l_stream << "Modification : " << m_modification << std::endl ;
      l_stream << "Deletion : " << m_deletion << std::endl ;
      l_stream << "--------------------------" << std::endl ;
      m_api.ui_append_log_text(*this,l_stream.str());
    }
  }

  //------------------------------------------------------------------------------
  const std::string & user_object_analyzer::get_input_type(void)const
  {
    return m_description.get_input_type();
  }

  //------------------------------------------------------------------------------
  const std::string & user_object_analyzer::get_output_type(void)const
  {
    return m_description.get_output_type();
  }

  //------------------------------------------------------------------------------
  const std::string & user_object_analyzer::get_type(void)const
  {
    return m_description.get_type();
  }

  user_object_analyzer_description user_object_analyzer::m_description;
}
//EOF
