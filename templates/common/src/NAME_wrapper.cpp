/*
    This file is part of osm_diff_analyzer_NAME, SAX based 
    Openstreetmap diff analyzer whose aim is to 
    Copyright (C) 2013  .....  ....... ( ........ at ......... )

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
#include "NAME_wrapper.h"
#include "NAME_analyzer_description.h"
#include "NAME_analyzer.h"
#include "NAME_common_api.h"
#include "quicky_exception.h"
#include <sstream>
#include <cassert>
#include <iostream>

namespace osm_diff_analyzer_NAME
{
  //----------------------------------------------------------------------------
  const char * NAME_wrapper::get_api_version(void)
  {
    return MODULE_LIBRARY_IF_VERSION;
  }

  //----------------------------------------------------------------------------
  uint32_t NAME_wrapper::get_api_size(void)
  {
    return MODULE_LIBRARY_IF_API_SIZE;
  }

  //----------------------------------------------------------------------------
  osm_diff_analyzer_if::analyzer_description_if * NAME_wrapper::get_NAME_description(void)
  {
    return new NAME_analyzer_description();
  }

  //----------------------------------------------------------------------------
  osm_diff_analyzer_if::general_analyzer_if * NAME_wrapper::create_NAME_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf)
  {
    return new NAME_analyzer(p_conf,*m_common_api);
  }

  //----------------------------------------------------------------------------
  void NAME_wrapper::require_common_api(osm_diff_analyzer_if::module_library_if::t_register_function p_func)
  {
    m_common_api = new NAME_common_api(p_func);
  }

  //----------------------------------------------------------------------------
  void NAME_wrapper::cleanup(void)
  {
    delete m_common_api;
  }
  NAME_common_api * NAME_wrapper::m_common_api = NULL;

  extern "C"
  {
    void register_module(uintptr_t* p_api,uint32_t p_api_size)
    {
      if(p_api_size != MODULE_LIBRARY_IF_API_SIZE)
	{
	  std::stringstream l_stream;
	  l_stream << "p_api_size < MODULE_LIBRARY_IF_API_SIZE : " << p_api_size << " < " << MODULE_LIBRARY_IF_API_SIZE << ". Please use a newer version of soda";
	  throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	}
#ifdef DEBUG
      std::cout << "Registration of NAME analyzer API " << std::endl ;
#endif
      p_api[osm_diff_analyzer_if::module_library_if::GET_API_VERSION] = (uintptr_t)NAME_wrapper::get_api_version;
      p_api[osm_diff_analyzer_if::module_library_if::GET_API_SIZE] = (uintptr_t)NAME_wrapper::get_api_size;
      p_api[osm_diff_analyzer_if::module_library_if::GET_DESCRIPTION] = (uintptr_t)NAME_wrapper::get_NAME_description;
      p_api[osm_diff_analyzer_if::module_library_if::CREATE_ANALYZER] = (uintptr_t)NAME_wrapper::create_NAME_analyzer;
      p_api[osm_diff_analyzer_if::module_library_if::REQUIRE_COMMON_API] = (uintptr_t)NAME_wrapper::require_common_api;
      p_api[osm_diff_analyzer_if::module_library_if::CLEAN_UP] = (uintptr_t)NAME_wrapper::cleanup;
    }
  }
}
//EOF
