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
#ifndef _DIFF_ANALYZER_IF_H_
#define _DIFF_ANALYZER_IF_H_

#include "general_analyzer_if.h"
#include "osm_diff_state.h"

namespace osm_diff_analyzer_if
{
  class diff_analyzer_if:public general_analyzer_if
  {
  public:
    virtual void init(const osm_diff_state * p_diff_state)=0;
    inline virtual ~diff_analyzer_if(void){};
  };
}

#endif // _OSM_DIFF_ANALYZER_IF_H_
//EOF
