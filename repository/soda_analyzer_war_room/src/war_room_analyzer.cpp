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
#include "war_room_analyzer.h"
#include "war_room_common_api.h"
#include "quicky_exception.h"
#include "my_bmp.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cassert>

namespace osm_diff_analyzer_war_room
{
  //------------------------------------------------------------------------------
  war_room_analyzer::war_room_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf,war_room_common_api & p_api):
    osm_diff_analyzer_sax_if::sax_analyzer_base("user_analyser",p_conf->get_name(),""),
    m_api(p_api),
    m_width(640),
    m_height(480),
    m_color(0),
    m_lat(0.0),
    m_lon(0.0),
    m_lat_min(-90.0),
    m_lat_max(90.0),
    m_lon_min(-180.0),
    m_lon_max(180.0),
    m_refresh_interval(0),
    m_count(0),
    m_size(5),
    m_buffer(NULL)
  {
    // Register module to be able to use User Interface
    m_api.ui_register_module(*this,get_name());

    const std::map<std::string,std::string> & l_conf_parameters = p_conf->get_parameters();

    // Width parameter management
    std::map<std::string,std::string>::const_iterator l_iter = l_conf_parameters.find("width");
    if(l_conf_parameters.end() != l_iter)
      {
	m_width = atoi(l_iter->second.c_str());
      }
    else
      {
	std::stringstream l_stream;
	l_stream << "Use default widht value " << m_width;
	m_api.ui_append_log_text(*this,l_stream.str());
      }

    l_iter = l_conf_parameters.find("height");
    if(l_conf_parameters.end() != l_iter)
      {
	m_height = atoi(l_iter->second.c_str());
      }
    else
      {
	std::stringstream l_stream;
	l_stream << "Use default height value " << m_width;
	m_api.ui_append_log_text(*this,l_stream.str());
      }

    l_iter = l_conf_parameters.find("refresh_interval");
    if(l_conf_parameters.end() != l_iter)
      {
	m_refresh_interval = atoi(l_iter->second.c_str());
      }
    else
      {
	std::stringstream l_stream;
	l_stream << "Use default refresh_interval value " << m_refresh_interval;
	m_api.ui_append_log_text(*this,l_stream.str());
      }

    std::string l_bmp_name;
    l_iter = l_conf_parameters.find("background_file");
    if(l_conf_parameters.end() != l_iter)
      {
        l_bmp_name = l_iter->second;
      }
    else
      {
	std::stringstream l_stream;
	l_stream << "No background file provided";
	m_api.ui_append_log_text(*this,l_stream.str());
      }
    get_parameter(m_size,"size",p_conf);

    get_double_parameter(m_lat_min,"lat_min",p_conf);
    get_double_parameter(m_lat_max,"lat_max",p_conf);
    get_double_parameter(m_lon_min,"lon_min",p_conf);
    get_double_parameter(m_lon_max,"lon_max",p_conf);

    m_gui.createWindow(m_width,m_height);
    m_color = m_gui.getColorCode(255,0,0);

    if(l_bmp_name != "")
      {
	m_gui.lock();
	my_bmp l_bmp(l_bmp_name);
	for(unsigned int l_x = 0 ; l_x < l_bmp.get_width();++l_x)
	  {
	    for(unsigned int l_y = 0 ; l_y < l_bmp.get_height();++l_y)
	      {
		my_color_alpha l_bmp_color = l_bmp.get_pixel_color(l_x,l_y);
		uint32_t l_sdl_color = m_gui.getColorCode(l_bmp_color.get_red(),l_bmp_color.get_green(),l_bmp_color.get_blue());
		m_gui.set_pixel_without_lock(l_x,l_y,l_sdl_color);
	      }
	  }
	m_buffer = m_gui.save_buffer();
	m_gui.unlock();
      }
    m_gui.refresh();
    m_gui.lock();

  }

  //------------------------------------------------------------------------------
  void war_room_analyzer::get_double_parameter(double & p_value,
					       const std::string & p_name,
					       const osm_diff_analyzer_if::module_configuration * p_conf)
  {
    const std::map<std::string,std::string> & l_conf_parameters = p_conf->get_parameters();

    // Width parameter management
    std::map<std::string,std::string>::const_iterator l_iter = l_conf_parameters.find(p_name);
    if(l_conf_parameters.end() != l_iter)
      {
	p_value = strtod(l_iter->second.c_str(),NULL);
      }
    else
      {
	std::stringstream l_stream;
	l_stream << "Use default \"" << p_name << "\" value : " << p_value;
	m_api.ui_append_log_text(*this,l_stream.str());
      }
  }

  //------------------------------------------------------------------------------
  void war_room_analyzer::get_parameter(unsigned int & p_value,
					const std::string & p_name,
					const osm_diff_analyzer_if::module_configuration * p_conf)
  {
    const std::map<std::string,std::string> & l_conf_parameters = p_conf->get_parameters();
    
    // Width parameter management
    std::map<std::string,std::string>::const_iterator l_iter = l_conf_parameters.find(p_name);
    if(l_conf_parameters.end() != l_iter)
      {
	p_value = atoi(l_iter->second.c_str());
      }
    else
      {
	std::stringstream l_stream;
	l_stream << "Use default \"" << p_name << "\" value : " << p_value;
	m_api.ui_append_log_text(*this,l_stream.str());
      }
  }

  //------------------------------------------------------------------------------
  war_room_analyzer::~war_room_analyzer(void)
  {
    m_gui.unlock();
  }

  //------------------------------------------------------------------------------
  void war_room_analyzer::init(const osm_diff_analyzer_if::osm_diff_state * p_diff_state)
  {
    m_gui.unlock();
    std::stringstream l_stream;
    l_stream << "Starting analyze of diff " << p_diff_state->get_sequence_number();
    m_api.ui_append_log_text(*this,l_stream.str());
    m_gui.refresh();
    m_gui.lock();
    if(!m_count)
      {
	m_count = m_refresh_interval + 1;
	m_gui.load_buffer(m_buffer);
      }
    --m_count;
  }

  //------------------------------------------------------------------------------
  void war_room_analyzer::start_element(const std::string & p_name)
  {
    m_lat = 0.0;
    m_lon = 0.0;
  }

  //------------------------------------------------------------------------------
  void war_room_analyzer::end_element(const std::string & p_name)
  {
    if(m_lat != 0.0 || m_lon != 0.0)
      {
	// Lat -90 + 90
	// Lon -180 _180
	//	uint32_t l_x = (m_lon + 180.0) *((double)m_width) / 360.0;
	//	uint32_t l_y = - (m_lat + 90.0) *((double)m_height) / 180.0 + m_height;
	uint32_t l_x = (m_lon - m_lon_min) *((double)m_width) / ( m_lon_max - m_lon_min);
	uint32_t l_y = - (m_lat - m_lat_min) *((double)m_height) / (m_lat_max - m_lat_min) + m_height;
#ifdef DEBUG
	std::stringstream l_stream;
	l_stream << "(lon,lat)=(" << m_lon << "," << m_lat << ") => (x,y)=(" << l_x << "," << l_y << ")";
	m_api.ui_append_log_text(*this,l_stream.str());
#endif
	for(int32_t l_render_x = l_x - m_size ; l_render_x <= (int32_t)l_x + (int32_t)m_size ; ++l_render_x)
	  {
	    if(l_render_x >= 0 && l_render_x < (int32_t)m_width)
	      {
		if(l_y - m_size >=0) m_gui.set_pixel_without_lock(l_render_x,l_y - m_size,m_color);
		if(l_y + m_size < m_height) m_gui.set_pixel_without_lock(l_render_x,l_y + m_size,m_color);
	      }
	  }

	for(int32_t l_render_y = l_y - m_size ; l_render_y <= (int32_t)l_y + (int32_t)m_size ; ++l_render_y)
	  {
	    if(l_render_y >= 0 && l_render_y < (int32_t)m_height)
	      {
		if(l_x - m_size >= 0) m_gui.set_pixel_without_lock(l_x - m_size,l_render_y,m_color);
		if(l_x + m_size < m_width) m_gui.set_pixel_without_lock(l_x + m_size,l_render_y,m_color);
	      }
	  }
      }
  }

  //------------------------------------------------------------------------------
  void war_room_analyzer::get_attribute(const std::string & p_name,const std::string & p_value)
  {
    if(p_name == "lat") m_lat = strtod(p_value.c_str(),NULL);
    if(p_name == "lon") m_lon = strtod(p_value.c_str(),NULL);
  }

  //------------------------------------------------------------------------------
  const std::string & war_room_analyzer::get_input_type(void)const
  {
    return m_description.get_input_type();
  }

  //------------------------------------------------------------------------------
  const std::string & war_room_analyzer::get_output_type(void)const
  {
    return m_description.get_output_type();
  }

  //------------------------------------------------------------------------------
  const std::string & war_room_analyzer::get_type(void)const
  {
    return m_description.get_type();
  }

  war_room_analyzer_description war_room_analyzer::m_description;
}
//EOF
