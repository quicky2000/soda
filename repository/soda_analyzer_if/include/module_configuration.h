/*
    This file is part of osm_diff_analyzer_if, Interface definitions of 
    libraries containing diff analyzers
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
#ifndef _MODULE_CONFIGURATION_H_
#define _MODULE_CONFIGURATION_H_

#include "quicky_exception.h"
#include <sstream>
#include <string>
#include <map>
#include <cassert>

namespace osm_diff_analyzer_if
{
  class module_configuration
  {
  public:
    inline module_configuration(const std::string & p_name,const std::string & p_type, bool p_enabled=true);
    inline void add_parameter(const std::string & p_name, const std::string & p_value);
    inline void remove_parameter(const std::string & p_name);
    inline const std::string & get_name(void)const;
    inline const std::string & get_type(void)const;
    inline bool is_enabled(void)const;
    inline const std::map<std::string,std::string> & get_parameters(void)const;
    inline bool is_parameter_defined(const std::string & p_name)const;
  private:
    const std::string m_name;
    const std::string m_type;
    bool m_enabled;
    std::map<std::string,std::string> m_parameters;
  };
  //----------------------------------------------------------------------------
  module_configuration::module_configuration(const std::string & p_name,const std::string & p_type, bool p_enabled):
    m_name(p_name),
    m_type(p_type),
    m_enabled(p_enabled)
  {
  }

  //----------------------------------------------------------------------------
  void module_configuration::add_parameter(const std::string & p_name, const std::string & p_value)
  {
    m_parameters.insert(make_pair(p_name,p_value));
  }

  //----------------------------------------------------------------------------
  void module_configuration::remove_parameter(const std::string & p_name)
  {
      std::map<std::string,std::string>::iterator l_iter = m_parameters.find(p_name);
      if(m_parameters.end() == l_iter)
        {
          std::stringstream l_stream;
          l_stream << "ERROR : try to remove parameter \"" << p_name << " which doesn't exist";
          throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
        }
      m_parameters.erase(l_iter);
  }

  //----------------------------------------------------------------------------
  bool module_configuration::is_parameter_defined(const std::string & p_name)const
  {
      return m_parameters.find(p_name) != m_parameters.end();
  }

  //----------------------------------------------------------------------------
  const std::string & module_configuration::get_name(void)const
  {
    return m_name;
  }
  
  //----------------------------------------------------------------------------
  const std::string & module_configuration::get_type(void)const
  {
    return m_type;
  }

  //----------------------------------------------------------------------------
  bool module_configuration::is_enabled(void)const
  {
    return m_enabled;
  }
  //----------------------------------------------------------------------------
  const std::map<std::string,std::string> & module_configuration::get_parameters(void)const
  {
    return m_parameters;
  }
}

#endif //_MODULE_CONFIGURATION_H_
//EOF
