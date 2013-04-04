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
#ifndef _OSM_DIFF_STATE_H_
#define _OSM_DIFF_STATE_H_

#include <string>
#include <inttypes.h>

namespace osm_diff_analyzer_if
{
  class osm_diff_state
  {
  public:
    inline osm_diff_state(const uint64_t & p_sequence_number,
                          const std::string & p_timestamp,
                          const std::string & p_replication_domain);
    inline const uint64_t & get_sequence_number(void)const;
    inline const std::string & get_timestamp(void)const;
    inline const std::string & get_replication_domain(void)const;
  private:
    const uint64_t m_sequence_number;
    const std::string m_timestamp;
    const std::string m_replication_domain;
  };

  //----------------------------------------------------------------------------
  osm_diff_state::osm_diff_state(const uint64_t & p_sequence_number,
                                 const std::string & p_timestamp,
                                 const std::string & p_replication_domain):
    m_sequence_number(p_sequence_number),
    m_timestamp(p_timestamp),
    m_replication_domain(p_replication_domain)
      {
      }

    //----------------------------------------------------------------------------
    const uint64_t & osm_diff_state::get_sequence_number(void)const
      {
        return m_sequence_number;
      }
    //----------------------------------------------------------------------------
    const std::string & osm_diff_state::get_timestamp(void)const
      {
        return m_timestamp;
      }
    //----------------------------------------------------------------------------
    const std::string & osm_diff_state::get_replication_domain(void)const
      {
        return m_replication_domain;
      }

}
#endif // _OSM_DIFF_STATE_H_
//EOF
