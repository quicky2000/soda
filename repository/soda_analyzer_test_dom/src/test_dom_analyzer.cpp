/*
    This file is part of osm_diff_analyzer_test_dom, Openstreetmap
    diff analyzer whose aim is to illustrate use of DOM API by just
    printing XML content
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
#include "test_dom_analyzer.h"
#include <iostream>
#include <sstream>

namespace osm_diff_analyzer_test_dom
{
  //------------------------------------------------------------------------------
  test_dom_analyzer::test_dom_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf,test_dom_common_api & p_api):
    dom_analyzer_base("test_dom",p_conf->get_name(),""),
    m_api(p_api),
    m_level(0)
  {
    // Register module to be able to use User Interface
    m_api.ui_register_module(*this,p_conf->get_name());
  }

  //------------------------------------------------------------------------------
  void test_dom_analyzer::analyze(const osm_diff_analyzer_dom_if::t_dom_tree & p_node)
  {
    {
      std::stringstream l_stream;
      l_stream  << "Level : " << m_level ;
      m_api.ui_append_log_text(*this,l_stream.str());
    }
    std::string l_tab(m_level,'|');
    l_tab +="|=> ";
    {
      std::stringstream l_stream;
      l_stream  << l_tab << "Element name : \"" << p_node.getName() << "\"" ;
      m_api.ui_append_log_text(*this,l_stream.str());
    }
    int l_nb_text_field = p_node.nText();
    if(l_nb_text_field)
      {
	{
	  std::stringstream l_stream;
	  l_stream  << l_tab << "Nb text fields : " << l_nb_text_field ;
	  m_api.ui_append_log_text(*this,l_stream.str());
	}
	for(int l_index=0;l_index<l_nb_text_field;++l_index)
	  {
	    {
	      std::stringstream l_stream;
	      l_stream  << l_tab << "text_field[" << l_index << "] = \"" << p_node.getText(l_index) << "\"" ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
	  }
      }
    int l_nb_attribute = p_node.nAttribute();
    if(l_nb_attribute)
      {
	for(int l_index=0;l_index<l_nb_attribute;++l_index)
	  {
	    XMLAttribute l_attribute = p_node.getAttribute(l_index);
	    {
	      std::stringstream l_stream;
	      l_stream  << l_tab << "attribute[\"" << l_attribute.lpszName << "\"]=\"" << l_attribute.lpszValue << "\"" ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
	  }
      }

    int l_nb_child_node = p_node.nChildNode();
    {
      std::stringstream l_stream;
      l_stream  << l_tab << "Nb child node : " << l_nb_child_node ;
      m_api.ui_append_log_text(*this,l_stream.str());
    }
    for(int l_index=0;l_index<l_nb_child_node;++l_index)
      {
	XMLNode l_node = p_node.getChildNode(l_index);
	++m_level;
	analyze(l_node);
	--m_level;
      }

  }

  //------------------------------------------------------------------------------
  const std::string & test_dom_analyzer::get_input_type(void)const
  {
    return m_description.get_input_type();
  }

  //------------------------------------------------------------------------------
  const std::string & test_dom_analyzer::get_output_type(void)const
  {
    return m_description.get_output_type();
  }

  //------------------------------------------------------------------------------
  const std::string & test_dom_analyzer::get_type(void)const
  {
    return m_description.get_type();
  }

  test_dom_analyzer_description test_dom_analyzer::m_description;
}
//EOF
