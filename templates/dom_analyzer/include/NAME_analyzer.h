/*
    This file is part of osm_diff_analyzer_NAME, DOM based
    Openstreetmap diff analyzer whose aim is to
    Copyright (C) 2013 ..... ............ ( ....... at ........ )

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
#ifndef _NAME_ANALYZER_H_
#define _NAME_ANALYZER_H_

#include "dom_analyzer_base.h"
#include "NAME_analyzer_description.h"
#include "module_configuration.h"

namespace osm_diff_analyzer_NAME
{
  class NAME_common_api;

  class NAME_analyzer: public osm_diff_analyzer_dom_if::dom_analyzer_base
  {
  public:
    NAME_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf,NAME_common_api & p_api);
    ~NAME_analyzer(void);
    // Methods inherited from dom_analyzer_if
    void analyze(const osm_diff_analyzer_dom_if::t_dom_tree & p_tree);
    const std::string & get_input_type(void)const;
    const std::string & get_output_type(void)const;
    const std::string & get_type(void)const;
    inline void init(const osm_diff_analyzer_if::osm_diff_state * p_diff_state){};
   // End if methods inherited from dom_analyzer_if
  private:
    NAME_common_api & m_api;
    static NAME_analyzer_description m_description;
  };
}
#endif // _NAME_ANALYZER_H_
//EOF
