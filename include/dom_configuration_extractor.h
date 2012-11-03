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
#ifndef _DOM_CONFIGURATION_EXTRACTOR_H_
#define _DOM_CONFIGURATION_EXTRACTOR_H_

#include "dom_simple_analyzer_if.h"
#include "configuration.h"
#include "xmlParser.h"
#include <cstring>

namespace osm_diff_watcher
{
  class dom_configuration_extractor: public dom_simple_analyzer_if
  {
  public:
    inline dom_configuration_extractor(void);
    // Method inherited from dom_analyzer_if
    inline void analyze(const osm_diff_analyzer_dom_if::t_dom_tree & p_tree);
    inline void init(void){}
    // end of Method inherited from dom_analyzer_if
    inline const configuration * get_result(void)const;
  private:
    configuration * m_result;
  };
  //----------------------------------------------------------------------------
  dom_configuration_extractor::dom_configuration_extractor(void):
    m_result(NULL)
    {
    }
    //--------------------------------------------------------------------------
    const configuration * dom_configuration_extractor::get_result(void)const
      {
	return m_result;
      }
    //--------------------------------------------------------------------------
    void dom_configuration_extractor::analyze(const osm_diff_analyzer_dom_if::t_dom_tree & p_tree)
    {
      assert(!strcmp("osm_diff_watcher_configuration",p_tree.getName()));
      m_result = new configuration();
      int l_nb_nodes = p_tree.nChildNode();
      for(int l_index = 0; l_index < l_nb_nodes ; ++l_index)
	{
	  osm_diff_analyzer_dom_if::t_dom_tree l_node = p_tree.getChildNode(l_index);
	  if(!strcmp(l_node.getName(),"library"))
	    {
	      XMLCSTR l_library_name = l_node.getAttribute("name");
              assert(l_library_name);
	      m_result->add_library(l_library_name);
	    }
	  else if(!strcmp(l_node.getName(),"analyzer"))
            {
	      XMLCSTR l_module_type = l_node.getAttribute("type");
              assert(l_module_type);
	      XMLCSTR l_module_name = l_node.getAttribute("name");
              assert(l_module_name);
	      XMLCSTR l_module_enabled = l_node.getAttribute("enabled");
	      bool l_enabled = true;
	      if(l_module_enabled)
		{
		  if(!strcmp(l_module_enabled,"no"))
		    {
		      l_enabled = false;
		    }
		  else if(strcmp(l_module_enabled,"yes"))
		    {
		      std::cout << "ERROR : \"enabled\" analyzer attribute should have vaue yes or no instead of \"" << l_module_enabled << "\"" << std::endl ;
		      exit(-1);
		    }
		}
	      osm_diff_analyzer_if::module_configuration * l_configuration = new osm_diff_analyzer_if::module_configuration(l_module_name,l_module_type,l_enabled);
	      int l_nb_param_nodes = l_node.nChildNode();
	      for(int l_param_index = 0 ;
		  l_param_index < l_nb_param_nodes;
		  ++l_param_index)
		{
		  osm_diff_analyzer_dom_if::t_dom_tree l_param_node = l_node.getChildNode(l_param_index);
		  std::cout << "node name \"" << l_param_node.getName() << "\"" << std::endl ;
		  if(strcmp(l_param_node.getName(),"parameter"))
		    {
		      std::cout << "ERROR : waiting for \"parameter\" node in configuration of module \"" << l_module_name << "\" instead of \"" <<  l_param_node.getName() << "\"" << std::endl ;
		      exit(-1);
		    }
		     XMLCSTR l_parameter_name = l_param_node.getAttribute("name");
		     assert(l_parameter_name);
		     XMLCSTR l_parameter_value = l_param_node.getAttribute("value");
		     assert(l_parameter_value);
		     l_configuration->add_parameter(l_parameter_name,l_parameter_value);
		}
	      m_result->add_module_configuration(l_configuration);
            }
	  else if(!strcmp(l_node.getName(),"variable"))
            {
	      XMLCSTR l_variable_name = l_node.getAttribute("name");
              assert(l_variable_name);
	      XMLCSTR l_variable_value = l_node.getAttribute("value");
              assert(l_variable_value);
	      m_result->add_variable(l_variable_name,l_variable_value);
            }
          else
	    {
	      std::cout << "ERROR : unknown configuration item \"" << l_node.getName() << "\"" << std::endl ;
	      exit(-1);
	    }
	}
   }

}
#endif // _DOM_CONFIGURATION_EXTRACTOR_H_
//EOF