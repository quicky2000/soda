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
#include "test_api_analyzer_description.h"

namespace osm_diff_analyzer_test_api
{
  //----------------------------------------------------------------------------
  const std::string & test_api_analyzer_description::get_input_type(void)const
  {
    return m_input_type;
  }

  //----------------------------------------------------------------------------
  const std::string & test_api_analyzer_description::get_output_type(void)const
  {
    return m_output_type;
  }

  //----------------------------------------------------------------------------
  const std::string & test_api_analyzer_description::get_type(void)const
  {
    return m_type;
  }

  const std::string test_api_analyzer_description::m_input_type = "sax";
  const std::string test_api_analyzer_description::m_output_type = "";
  const std::string test_api_analyzer_description::m_type = "test_api";

}
//EOF
