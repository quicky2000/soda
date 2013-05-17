/*
  This file is part of osm_diff_analyzer_NAME, Openstreetmap
  diff analyzer based on CPP diff representation. It's aim is to survey
  editions concerning a specified tag
  Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#ifndef _NAME_ANALYZER_H_
#define _NAME_ANALYZER_H_

#include "cpp_analyzer_base.h"
#include "NAME_analyzer_description.h"
#include "NAME_common_api.h"
#include "module_configuration.h"

namespace osm_diff_analyzer_NAME
{
  class NAME_common_api;

  class NAME_analyzer:public osm_diff_analyzer_cpp_if::cpp_analyzer_base
  {
  public:
    NAME_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf,NAME_common_api & p_api);
    ~NAME_analyzer(void);
    // Methods inherited from cpp_analyzer_if
    void init(const osm_diff_analyzer_if::osm_diff_state * p_diff_state);
    void analyze(const std::vector<osm_api_data_types::osm_change*> & p_changes);
    const std::string & get_input_type(void)const;
    const std::string & get_output_type(void)const;
    const std::string & get_type(void)const;
    // End of inherited methods
  private:
    template <class T>
      void generic_analyze(const osm_api_data_types::osm_core_element * const p_object,
			   const osm_api_data_types::osm_change::t_osm_change_type & p_change);
    void treat(const osm_api_data_types::osm_node & p_node,
	       const osm_api_data_types::osm_change::t_osm_change_type & p_change);
    void treat(const osm_api_data_types::osm_way & p_way,
	       const osm_api_data_types::osm_change::t_osm_change_type & p_change);
    void treat(const osm_api_data_types::osm_relation & p_relation,
	       const osm_api_data_types::osm_change::t_osm_change_type & p_change);
    NAME_common_api & m_api;
    static NAME_analyzer_description m_description;
  };

  //------------------------------------------------------------------------------
  template <class T>
    void NAME_analyzer::generic_analyze(const osm_api_data_types::osm_core_element * const p_object,
					       const osm_api_data_types::osm_change::t_osm_change_type & p_change)
    {

#ifndef FORCE_USE_OF_REINTERPRET_CAST
      const T * const l_casted_object = dynamic_cast<const T * const>(p_object);
#else
      const T * const l_casted_object = reinterpret_cast<const T * const>(p_object);
#endif // FORCE_USE_OF_REINTERPRET_CAST
 
      // Check if cast has been successfull
     if(l_casted_object==NULL)
        {
          std::stringstream l_stream;
          l_stream << "ERROR : invalid " << T::get_type_str() << " cast for object id " << p_object->get_id();
          throw quicky_exception::quicky_logic_exception(l_stream.str(),__LINE__,__FILE__);
        }

     // Call the treatment function corresponding to object type
     treat(*l_casted_object,p_change);
    }


}
#endif
