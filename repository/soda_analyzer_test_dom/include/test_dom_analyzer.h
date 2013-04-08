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
#ifndef _TEST_DOM_ANALYZER_H_
#define _TEST_DOM_ANALYZER_H_

#include "dom_analyzer_base.h"
#include "test_dom_analyzer_description.h"
#include "module_configuration.h"
#include "test_dom_common_api.h"

namespace osm_diff_analyzer_test_dom
{
  class test_dom_analyzer: public osm_diff_analyzer_dom_if::dom_analyzer_base
  {
  public:
    test_dom_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf,test_dom_common_api & p_api);
    // Methods inherited from dom_analyzer_if
    void analyze(const osm_diff_analyzer_dom_if::t_dom_tree & p_tree);
    const std::string & get_input_type(void)const;
    const std::string & get_output_type(void)const;
    const std::string & get_type(void)const;
    inline void init(const osm_diff_analyzer_if::osm_diff_state * p_diff_state){};
   // End if methods inherited from dom_analyzer_if
  private:
    test_dom_common_api & m_api;
    std::string m_name;
    unsigned int m_level;

    static test_dom_analyzer_description m_description;
  };
}
#endif // _TEST_DOM_ANALYZER_H_
//EOF
