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
#include "test_dom_wrapper.h"
#include "test_dom_analyzer_description.h"
#include "test_dom_analyzer.h"
#include "quicky_exception.h"
#include "test_dom_common_api.h"
#include <sstream>
#include <cassert>
#include <iostream>

namespace osm_diff_analyzer_test_dom
{
  //----------------------------------------------------------------------------
  osm_diff_analyzer_if::general_analyzer_if * test_dom_wrapper::create_test_dom_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf)
  {
    return new test_dom_analyzer(p_conf,*m_common_api);
  }

  //----------------------------------------------------------------------------
  osm_diff_analyzer_if::analyzer_description_if * test_dom_wrapper::get_test_dom_description(void)
  {
    return new test_dom_analyzer_description();
  }

  //----------------------------------------------------------------------------
  const char * test_dom_wrapper::get_api_version(void)
  {
    return MODULE_LIBRARY_IF_VERSION;
  }

  //----------------------------------------------------------------------------
  uint32_t test_dom_wrapper::get_api_size(void)
  {
    return MODULE_LIBRARY_IF_API_SIZE;
  }

  //----------------------------------------------------------------------------
  void test_dom_wrapper::require_common_api(osm_diff_analyzer_if::module_library_if::t_register_function p_func)
  {
    m_common_api = new test_dom_common_api(p_func);
  }

  //----------------------------------------------------------------------------
  void test_dom_wrapper::cleanup(void)
  {
    delete m_common_api;
  }

  test_dom_common_api * test_dom_wrapper::m_common_api = NULL;

  extern "C"
  {
    void register_module(uintptr_t* p_api,uint32_t p_api_size)
    {
      if(p_api_size != MODULE_LIBRARY_IF_API_SIZE)
	{
	  std::stringstream l_stream;
	  l_stream << "p_api_size != MODULE_LIBRARY_IF_API_SIZE : " << p_api_size << " < " << MODULE_LIBRARY_IF_API_SIZE << ". Please use a newver version of saoda";
	  throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
	}
#ifdef DEBUG
      std::cout << "Registration of test_dom analyzer API " << std::endl ;
#endif
      p_api[osm_diff_analyzer_if::module_library_if::GET_API_VERSION] = (uintptr_t)test_dom_wrapper::get_api_version;
      p_api[osm_diff_analyzer_if::module_library_if::GET_API_SIZE] = (uintptr_t)test_dom_wrapper::get_api_size;
      p_api[osm_diff_analyzer_if::module_library_if::GET_DESCRIPTION] = (uintptr_t)test_dom_wrapper::get_test_dom_description;
      p_api[osm_diff_analyzer_if::module_library_if::CREATE_ANALYZER] = (uintptr_t)test_dom_wrapper::create_test_dom_analyzer;
      p_api[osm_diff_analyzer_if::module_library_if::REQUIRE_COMMON_API] = (uintptr_t)test_dom_wrapper::require_common_api;
      p_api[osm_diff_analyzer_if::module_library_if::CLEAN_UP] = (uintptr_t)test_dom_wrapper::cleanup;
    }
  }
}
//EOF
