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
#ifndef _OSM_CHANGESET_H_
#define _OSM_CHANGESET_H_

#include "osm_object.h"
#include "osm_bounding_box.h"

namespace osm_api_data_types
{
  class osm_changeset: public osm_object
  {
    friend std::ostream & operator<<(std::ostream & p_stream,const osm_changeset & p_changeset);
  public:
    inline osm_changeset(const t_osm_id  & p_id,
                         const t_osm_id & p_user_id,
                         const std::string & p_user,
                         const std::string & p_created_at,
                         const std::string & p_closed_at,
                         bool p_open,
                         const osm_bounding_box & p_bounding_box
                         );
    inline const std::string & get_created_at(void)const;
    inline const std::string & get_closed_at(void)const;
    inline bool is_open(void)const;
    inline const osm_bounding_box & get_bounding_box(void)const;
    inline static const std::string & get_type_str(void);
  private:
    const std::string m_created_at;
    const std::string m_closed_at;
    bool m_open;
    osm_bounding_box m_bounding_box;
    static const std::string m_type;
  }
  ;

  //------------------------------------------------------------------------------
  inline std::ostream & operator<<(std::ostream & p_stream,const osm_changeset & p_changeset)
    {
      p_stream << "changeset id=" << p_changeset.get_id() << " user=\"" << p_changeset.get_user() << "\" created_at=\"" << p_changeset.get_created_at() << "\" closed_at=\"" << p_changeset.get_closed_at() << "\" open=" << p_changeset.is_open() << std::endl ;
      std::string l_tags_str;
      p_changeset.tags_to_string(l_tags_str);
      p_stream << l_tags_str ;
      return p_stream;
    }

  //----------------------------------------------------------------------------
  osm_changeset::osm_changeset(const t_osm_id  & p_id,
                               const t_osm_id & p_user_id,
                               const std::string & p_user,
                               const std::string & p_created_at,
                               const std::string & p_closed_at,
                               bool p_open,
                               const osm_bounding_box & p_bounding_box
                               ):
    osm_object(p_id,p_user_id,p_user),
    m_created_at(p_created_at),
    m_closed_at(p_closed_at),
    m_open(p_open),
    m_bounding_box(p_bounding_box)
      {
      }

    //----------------------------------------------------------------------------
    const std::string & osm_changeset::get_created_at(void)const
      {
        return m_created_at;
      }

    //----------------------------------------------------------------------------
    const std::string & osm_changeset::get_closed_at(void)const
      {
        return m_closed_at;
      }

    //----------------------------------------------------------------------------
    bool osm_changeset::is_open(void)const
    {
      return m_open;
    }

    //----------------------------------------------------------------------------
    const osm_bounding_box & osm_changeset::get_bounding_box(void)const
      {
        return m_bounding_box;
      }

    //----------------------------------------------------------------------------
    const std::string & osm_changeset::get_type_str(void)
    {
      return m_type;
    }
}
#endif // _OSM_CHANGESET_H_
//EOF
