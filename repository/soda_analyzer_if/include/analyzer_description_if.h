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
#ifndef _ANALYZER_DESCRIPTION_IF_H_
#define _ANALYZER_DESCRIPTION_IF_H_

#include <string>

namespace osm_diff_analyzer_if
{
  class analyzer_description_if
  {
  public:
    virtual const std::string & get_input_type(void)const=0;
    virtual const std::string & get_output_type(void)const=0;
    virtual const std::string & get_type(void)const=0;
    virtual ~analyzer_description_if(void){};
  private:
  };
}
#endif //_ANALYZER_DESCRIPTION_IF_H
//EOF
