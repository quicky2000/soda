/*
    This file is part of osm_diff_analyzer_cpp_if, Interface definitions 
    of based Openstreetmap diff analyzers receiving C++ represenation of
    Openstreetmap diff content
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
#ifndef _CPP_ANALYZER_IF_H_
#define _CPP_ANALYZER_IF_H_

#include "diff_analyzer_if.h"
#include "osm_change.h"
#include <string>
#include <vector>

namespace osm_diff_analyzer_cpp_if
{
  class cpp_analyzer_if: public osm_diff_analyzer_if::diff_analyzer_if
  {
  public:
    virtual void analyze(const std::vector<osm_api_data_types::osm_change*> & p_changes)=0;

    inline virtual ~cpp_analyzer_if(void){};
  };
}
#endif
//EOF
