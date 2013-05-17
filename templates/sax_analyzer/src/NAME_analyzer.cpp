/*
  This file is part of osm_diff_analyzer_NAME, SAX based 
  Openstreetmap diff analyzer whose aim is 
  Copyright (C) 2013  ....... ........ ( ......... at ........... )

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

namespace osm_diff_analyzer_NAME
{
  //------------------------------------------------------------------------------
  NAME_analyzer::NAME_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf,NAME_common_api & p_api):
    osm_diff_analyzer_sax_if::sax_analyzer_base("NAME_analyser",p_conf->get_name(),""),
    m_api(p_api)
  {
    // The following line of code register module to be able to use User Interface
    m_api.ui_register_module(*this,get_name());

    // Get configuration parameters
    // const std::map<std::string,std::string> & l_conf_parameters = p_conf->get_parameters();

    // Put here the code to initialise the module, treat configuration parameters etc
  }

  //------------------------------------------------------------------------------
  NAME_analyzer::~NAME_analyzer(void)
  {
    // Analyzer destructor. It will be called at the end of the execution
    // Put here the code that will terminate the analyze
  }

  //------------------------------------------------------------------------------
  void NAME_analyzer::init(const osm_diff_analyzer_if::osm_diff_state * p_diff_state)
  {
    // This method will be called at the beginning of each diff file analyse
    // p_diff_state parameter contains some information about the diff file like its sequence number
  }

  //------------------------------------------------------------------------------
  void NAME_analyzer::start_element(const std::string & p_name)
  {
    // In this method put the initialisation corresponding to this element
  }

  //------------------------------------------------------------------------------
  void NAME_analyzer::end_element(const std::string & p_name)
  {
    // In this method put the treatment of all data collected since the beginning of the element
  }

  //------------------------------------------------------------------------------
  void NAME_analyzer::get_attribute(const std::string & p_name,const std::string & p_value)
  {
    // In this method put the code that will treat each attribute of XML elements
    // This is typically something like if(p_name == "ELEMENT) do_something(p_value)"
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
