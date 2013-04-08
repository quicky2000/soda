/*
    This file is part of osm_diff_analyzer_test_api, Openstreetmap
    diff analyzer whose aim is to test API allowing to analyzers to get
    OSM object information through OSM API implementation provided by
    diff analyzis framewwork
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
#ifndef _TEST_API_ANALYZER_H_
#define _TEST_API_ANALYZER_H_

#include "sax_analyzer_base.h"
#include "test_api_analyzer_description.h"
#include "module_configuration.h"
#include <inttypes.h>
#include <map>
#include <fstream>

namespace osm_diff_analyzer_test_api
{
  class common_api;

  class test_api_analyzer:public osm_diff_analyzer_sax_if::sax_analyzer_base
  {
  public:
    test_api_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf,common_api & p_api);
    ~test_api_analyzer(void);
    // Methods inherited from sax_analyzer_if
    void init(const osm_diff_analyzer_if::osm_diff_state * p_diff_state);
    void start_element(const std::string & p_name);
    void get_attribute(const std::string & p_name,const std::string & p_value);
    void end_element(const std::string & p_name);
    const std::string & get_input_type(void)const;
    const std::string & get_output_type(void)const;
    const std::string & get_type(void)const;
    // End of inherited methods
  private:
    common_api & m_api;
    bool m_done;
     static test_api_analyzer_description m_description;
 };
}
#endif
