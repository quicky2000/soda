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
#include "osm_core_element.h"

namespace osm_api_data_types
{
  std::map<std::string,osm_core_element::t_osm_type> osm_core_element::m_osm_types;
  std::map<osm_core_element::t_osm_type,std::string> osm_core_element::m_osm_types_str;
}
//EOF
