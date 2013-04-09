/*
    This file is part of osm_diff_analyzer_war_room, SAX based 
    Openstreetmap diff analyzer whose aim is to detect users arrived
    in Openstreetmap Project for less than 3 Months
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
#ifndef _WAR_ROOM_ANALYZER_H_
#define _WAR_ROOM_ANALYZER_H_

#include "sax_analyzer_base.h"
#include "war_room_analyzer_description.h"
#include "module_configuration.h"
#include "osm_api_data_types.h"
#include "simple_gui.h"

#include <inttypes.h>
#include <map>
#include <fstream>

namespace osm_diff_analyzer_war_room
{
  class war_room_common_api;

  class war_room_analyzer:public osm_diff_analyzer_sax_if::sax_analyzer_base
  {
  public:
    war_room_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf,war_room_common_api & p_api);
    ~war_room_analyzer(void);
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
    void get_double_parameter(double & p_value,
			      const std::string & p_name,
			      const osm_diff_analyzer_if::module_configuration * p_conf);
    void get_parameter(unsigned int & p_value,
		       const std::string & p_name,
		       const osm_diff_analyzer_if::module_configuration * p_conf);
    simple_gui m_gui;
    war_room_common_api & m_api;
    unsigned int m_width;
    unsigned int m_height;
    uint32_t m_color;
    double m_lat;
    double m_lon;
    double m_lat_min;
    double m_lat_max;
    double m_lon_min;
    double m_lon_max;
    unsigned int m_refresh_interval;
    unsigned int m_count;
    unsigned int m_size;
    void * m_buffer;
    static war_room_analyzer_description m_description;
  };
}
#endif
