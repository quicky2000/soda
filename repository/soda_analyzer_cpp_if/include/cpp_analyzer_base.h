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
#ifndef _CPP_ANALYZER_BASE_H_
#define _CPP_ANALYZER_BASE_H_

#include "analyzer_base.h"
#include "cpp_analyzer_if.h"

namespace osm_diff_analyzer_cpp_if
{
  class cpp_analyzer_base: public osm_diff_analyzer_if::analyzer_base, public cpp_analyzer_if
  {
  public:
    inline cpp_analyzer_base(const std::string & p_type,
			     const std::string & p_name,
			     const std::string & p_output_type);
    inline const std::string & get_name(void)const;
  private:
  };
  //----------------------------------------------------------------------------
  cpp_analyzer_base::cpp_analyzer_base(const std::string & p_type,
				       const std::string & p_name,
				       const std::string & p_output_type):
    osm_diff_analyzer_if::analyzer_base(p_type,p_name,"cpp",p_output_type)
    {
    }
    //----------------------------------------------------------------------------
    const std::string & cpp_analyzer_base::get_name(void)const
      {
        return osm_diff_analyzer_if::analyzer_base::get_name();
      }
}
#endif // _CPP_ANALYZER_BASE_H_
//EOF
