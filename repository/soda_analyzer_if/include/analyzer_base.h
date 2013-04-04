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
#ifndef _ANALYZER_BASE_H_
#define _ANALYZER_BASE_H_

#include <string>

namespace osm_diff_analyzer_if
{
  class analyzer_base
  {
  public:
    inline analyzer_base(const std::string & p_type,
			 const std::string & p_name,
			 const std::string & p_input_type,
			 const std::string & p_output_type);
    inline const std::string & get_name(void)const;
    inline const std::string & get_input_type(void)const;
    inline const std::string & get_output_type(void)const;
    inline const std::string & get_type(void)const;
  private:
    std::string m_type;
    std::string m_name;
    std::string m_input_type;
    std::string m_output_type;
  };

  //----------------------------------------------------------------------------
  analyzer_base::analyzer_base(const std::string & p_type,
			       const std::string & p_name,
			       const std::string & p_input_type,
			       const std::string & p_output_type):
    m_type(p_type),
    m_name(p_name),
    m_input_type(p_input_type),
    m_output_type(p_output_type)
    {
    }

  //----------------------------------------------------------------------------
  const std::string & analyzer_base::get_name(void)const
    {
      return m_name;
    }

  //----------------------------------------------------------------------------
  const std::string & analyzer_base::get_input_type(void)const
    {
      return m_input_type;
    }

  //----------------------------------------------------------------------------
  const std::string & analyzer_base::get_output_type(void)const
    {
      return m_output_type;
    }

  //----------------------------------------------------------------------------
  const std::string & analyzer_base::get_type(void)const
    {
      return m_type;
    }
}

#endif // _ANALYZER_BASE_H_
//EOF
