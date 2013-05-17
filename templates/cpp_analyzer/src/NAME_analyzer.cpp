/*
  This file is part of osm_diff_analyzer_NAME, Openstreetmap
  diff analyzer based on CPP diff representation. It's aim is to
  Copyright (C) 2013  ...... ......... ( ........ at ........ )

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
#include "NAME_analyzer.h"
#include "NAME_common_api.h"
#include "quicky_exception.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstring>

namespace osm_diff_analyzer_NAME
{
  //------------------------------------------------------------------------------
  NAME_analyzer::NAME_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf,
                                           NAME_common_api & p_api):
    osm_diff_analyzer_cpp_if::cpp_analyzer_base("NAME_analyser",p_conf->get_name(),""),
    m_api(p_api)
  {
    // Register module to be able to use User Interface
    m_api.ui_register_module(*this,get_name());

    // Getting configuration parameters
    const std::map<std::string,std::string> & l_conf_parameters = p_conf->get_parameters();
  }

  //------------------------------------------------------------------------------
  NAME_analyzer::~NAME_analyzer(void)
  {
  }

  //------------------------------------------------------------------------------
  void NAME_analyzer::init(const osm_diff_analyzer_if::osm_diff_state * p_diff_state)
  {
  }

  //------------------------------------------------------------------------------
  void NAME_analyzer::analyze(const std::vector<osm_api_data_types::osm_change*> & p_changes)
  {
    for(std::vector<osm_api_data_types::osm_change*>::const_iterator l_iter = p_changes.begin();
        l_iter != p_changes.end();
        ++l_iter)
      {
        const osm_api_data_types::osm_core_element * const l_element = (*l_iter)->get_core_element();
        if(l_element == NULL) throw quicky_exception::quicky_logic_exception("core_element should not be NULL",__LINE__,__FILE__);

        switch(l_element->get_core_type())
          {
          case osm_api_data_types::osm_core_element::NODE :
	    generic_analyze<osm_api_data_types::osm_node>(l_element,(*l_iter)->get_type());
            break;
          case osm_api_data_types::osm_core_element::WAY :
	    generic_analyze<osm_api_data_types::osm_way>(l_element,(*l_iter)->get_type());
            break;
          case osm_api_data_types::osm_core_element::RELATION :
	    generic_analyze<osm_api_data_types::osm_relation>(l_element,(*l_iter)->get_type());
            break;
          case osm_api_data_types::osm_core_element::INTERNAL_INVALID:
	    {
	      std::stringstream l_stream;
	      l_stream << "ERROR : unexpected core type value \"" << osm_api_data_types::osm_core_element::get_osm_type_str(l_element->get_core_type()) << "\"" ;
	      throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	    }
            break;
          }

      }
  }

  //------------------------------------------------------------------------------
  void NAME_analyzer::treat(const osm_api_data_types::osm_node & p_node,
			    const osm_api_data_types::osm_change::t_osm_change_type & p_change)
  {
    switch(p_change)
      {
      case osm_api_data_types::osm_change::CREATION:
	// Put here the code to treat node creation
	break;
      case osm_api_data_types::osm_change::MODIFICATION:
	// Put here the code to treat node modification
	break;
      case osm_api_data_types::osm_change::DELETION:
	// Put here the code to treat node deletion
	break;
      case osm_api_data_types::osm_change::INTERNAL_INVALID:
	// This should normally never occur
	// For more safety launch an exception
      default:
	break;
      }
  }

  //------------------------------------------------------------------------------
  void NAME_analyzer::treat(const osm_api_data_types::osm_way & p_way,
			    const osm_api_data_types::osm_change::t_osm_change_type & p_change)
  {
    switch(p_change)
      {
      case osm_api_data_types::osm_change::CREATION:
	// Put here the code to treat way creation
	break;
      case osm_api_data_types::osm_change::MODIFICATION:
	// Put here the code to treat way modification
	break;
      case osm_api_data_types::osm_change::DELETION:
	// Put here the code to treat way deletion
	break;
      case osm_api_data_types::osm_change::INTERNAL_INVALID:
	// This should normally never occur
	// For more safety launch an exception
      default:
	break;
      }
  }

  //------------------------------------------------------------------------------
  void NAME_analyzer::treat(const osm_api_data_types::osm_relation & p_relation,
			    const osm_api_data_types::osm_change::t_osm_change_type & p_change)
  {
    switch(p_change)
      {
      case osm_api_data_types::osm_change::CREATION:
	// Put here the code to treat relation creation
	break;
      case osm_api_data_types::osm_change::MODIFICATION:
	// Put here the code to treat relation modification
	break;
      case osm_api_data_types::osm_change::DELETION:
	// Put here the code to treat relation deletion
	break;
      case osm_api_data_types::osm_change::INTERNAL_INVALID:
	// This should normally never occur
	// For more safety launch an exception
      default:
	break;
      }
  }

  //------------------------------------------------------------------------------
  const std::string & NAME_analyzer::get_input_type(void)const
  {
    return m_description.get_input_type();
  }

  //------------------------------------------------------------------------------
  const std::string & NAME_analyzer::get_output_type(void)const
  {
    return m_description.get_output_type();
  }

  //------------------------------------------------------------------------------
  const std::string & NAME_analyzer::get_type(void)const
  {
    return m_description.get_type();
  }

  NAME_analyzer_description NAME_analyzer::m_description;
}
//EOF
