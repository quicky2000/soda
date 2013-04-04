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
#ifndef _OSM_BOUNDING_BOX_H_
#define _OSM_BOUNDING_BOX_H_

namespace osm_api_data_types
{
  class osm_bounding_box
  {
  public:
    inline osm_bounding_box(void);
    inline osm_bounding_box(const float & p_min_lat,
                            const float & p_min_lon,
                            const float & p_max_lat,
                            const float & p_max_lon);
    inline bool is_empty(void)const;
    inline const float & get_min_lat(void)const;
    inline const float & get_min_lon(void)const;
    inline const float & get_max_lat(void)const;
    inline const float & get_max_lon(void)const;
    inline bool contains(const float & p_lat,const float & p_lon)const;
  private:
    bool m_empty;
    float m_min_lat;
    float m_min_lon;
    float m_max_lat;
    float m_max_lon;
  };
  //----------------------------------------------------------------------------
  osm_bounding_box::osm_bounding_box(void):
    m_empty(true),
    m_min_lat(0.0),
    m_min_lon(0.0),
    m_max_lat(0.0),
    m_max_lon(0.0)
  {
  }

  //----------------------------------------------------------------------------
  osm_bounding_box::osm_bounding_box(const float & p_min_lat,
                                     const float & p_min_lon,
                                     const float & p_max_lat,
                                     const float & p_max_lon):
    m_empty(false),
    m_min_lat(p_min_lat),
    m_min_lon(p_min_lon),
    m_max_lat(p_max_lat),
    m_max_lon(p_max_lon)
    {
    }

    //----------------------------------------------------------------------------
    bool osm_bounding_box::is_empty(void)const
    {
      return m_empty;
    }

  //----------------------------------------------------------------------------
  const float & osm_bounding_box::get_min_lat(void)const
    {
      return m_min_lat;
    }

  //----------------------------------------------------------------------------
  const float & osm_bounding_box::get_min_lon(void)const
    {
      return m_min_lon;
    }

  //----------------------------------------------------------------------------
  const float & osm_bounding_box::get_max_lat(void)const
    {
      return m_max_lat;
    }

  //----------------------------------------------------------------------------
  const float & osm_bounding_box::get_max_lon(void)const
    {
      return m_max_lon;
    }

  //----------------------------------------------------------------------------
  bool osm_bounding_box::contains(const float & p_lat,const float & p_lon)const
  {
    return m_min_lat <= p_lat && p_lat <= m_max_lat && m_min_lon <= p_lon && p_lon <= m_max_lon;
  }

}
#endif // _OSM_BOUNDING_BOX_H_
//EOF
