/*
    This file is part of osm_api_data_types, C++ representation of Openstreetmap
    API 0.6 primitive objects
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
#ifndef _OSM_RELATION_MEMBER_H_
#define _OSM_RELATION_MEMBER_H_

#include "osm_core_element.h"

namespace osm_api_data_types
{
  class osm_relation_member
  {
    friend std::ostream & operator<<(std::ostream & p_stream,const osm_relation_member & p_relation_member);
  public:
    inline osm_relation_member(const osm_core_element::t_osm_type & p_type,
                               const osm_object::t_osm_id & p_object_ref,
                               const std::string & p_role);
    inline const osm_core_element::t_osm_type & get_type(void)const;
    inline const osm_object::t_osm_id & get_object_ref(void)const;
    inline const std::string & get_role(void)const;
  private:
    const osm_core_element::t_osm_type m_type;
    const osm_object::t_osm_id m_object_ref;
    const std::string m_role;
  };

  //------------------------------------------------------------------------------
  inline std::ostream & operator<<(std::ostream & p_stream,const osm_relation_member & p_relation_member)
    {
      p_stream << "relation_member type=" << osm_core_element::get_osm_type_str(p_relation_member.m_type) << " object_ref=" << p_relation_member.m_object_ref << " role=\"" << p_relation_member.m_role << "\"" << std::endl ;
      return p_stream;
    }

  //----------------------------------------------------------------------------
  osm_relation_member::osm_relation_member(const osm_core_element::t_osm_type & p_type,
                                           const osm_object::t_osm_id & p_object_ref,
                                           const std::string & p_role):
    m_type(p_type),
    m_object_ref(p_object_ref),
    m_role(p_role)
      {
      }
  
    
    //----------------------------------------------------------------------------
    const osm_core_element::t_osm_type & osm_relation_member::get_type(void)const
      {
        return m_type;
      }

    //----------------------------------------------------------------------------
    const osm_object::t_osm_id & osm_relation_member::get_object_ref(void)const
      {
        return m_object_ref;
      }

    //----------------------------------------------------------------------------
    const std::string & osm_relation_member::get_role(void)const
      {
        return m_role;
      }
}

#endif // _OSM_RELATION_MEMBER_H_
//EOF
