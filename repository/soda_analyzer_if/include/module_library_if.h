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
#ifndef _MODULE_LIBRARY_IF_H_
#define _MODULE_LIBRARY_IF_H_

#include "general_analyzer_if.h"
#include "module_configuration.h"
#include <inttypes.h>

namespace osm_diff_analyzer_if
{
#define MODULE_LIBRARY_IF_VERSION "0.1"
#define MODULE_LIBRARY_IF_API_SIZE 6

  class module_library_if
  {
  public:

    typedef void(*t_register_function)(uintptr_t *,uint32_t);

    typedef general_analyzer_if*(*t_create_analyzer)(const module_configuration * p_conf);
    typedef analyzer_description_if * (*t_get_description)(void);
    typedef const char *(*t_get_api_version)(void);
    typedef uint32_t(*t_get_api_size)(void);
    typedef void (*t_require_common_api)(t_register_function);
    typedef void (*t_cleanup)(void);
    typedef enum /* class */ {GET_API_VERSION=0,
                              GET_API_SIZE,
			      GET_DESCRIPTION,
			      CREATE_ANALYZER,
			      REQUIRE_COMMON_API,
                              CLEAN_UP} t_module_library_index;
  };
}
#endif // _MODULE_LIBRARY_IF_H_
//EOF
