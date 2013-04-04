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
#ifndef _COMMON_API_IF_H_
#define _COMMON_API_IF_H_

#include "module_library_if.h"
#include "osm_node.h"
#include "osm_way.h"
#include "osm_relation.h"
#include "osm_changeset.h"
#include "osm_change.h"

namespace osm_diff_analyzer_if
{
#define COMMON_API_IF_VERSION "0.3"
#define COMMON_API_IF_SIZE 36
  class analyzer_base;

  class common_api_if
  {
  public:
    typedef const char *(*t_get_api_version)(void);

    typedef void (*t_get_user_subscription_date)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                 const std::string & p_name,
                                                 std::string & p_date,
						 void * p_user_data); 

    typedef const osm_api_data_types::osm_node * (*t_get_node)(const osm_api_data_types::osm_object::t_osm_id & p_id,
							       void * p_user_data);

    typedef const osm_api_data_types::osm_node * (*t_get_node_version)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                       const osm_api_data_types::osm_core_element::t_osm_version & p_version,
                                                                       void * p_user_data);

    typedef const std::vector<osm_api_data_types::osm_node*> * const (*t_get_node_history)(const osm_api_data_types::osm_object::t_osm_id & p_id,
											   void * p_user_data);

    typedef const std::vector<osm_api_data_types::osm_way*> * const (*t_get_node_ways)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                                       void * p_user_data);

    typedef const std::vector<osm_api_data_types::osm_relation*> * const (*t_get_node_relations)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                                                 void * p_user_data);

    typedef const std::vector<osm_api_data_types::osm_node*> * const (*t_get_nodes)(const std::vector<osm_api_data_types::osm_object::t_osm_id> & p_ids,
										    void * p_user_data);

    typedef const osm_api_data_types::osm_way * (*t_get_way)(const osm_api_data_types::osm_object::t_osm_id & p_id,
							     void * p_user_data);

    typedef const osm_api_data_types::osm_way * (*t_get_way_version)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                     const osm_api_data_types::osm_core_element::t_osm_version & p_version,
                                                                     void * p_user_data);

    typedef const std::vector<osm_api_data_types::osm_way*> * const (*t_get_way_history)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                                         void * p_user_data);

    typedef const std::vector<osm_api_data_types::osm_relation*> * const (*t_get_way_relations)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                                                void * p_user_data);

    typedef const osm_api_data_types::osm_way * const (*t_get_way_full)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                        std::vector<osm_api_data_types::osm_node*> & p_nodes,
                                                                        void * p_user_data);

    typedef const std::vector<osm_api_data_types::osm_way*> * const (*t_get_ways)(const std::vector<osm_api_data_types::osm_object::t_osm_id> & p_ids,
                                                                                  void * p_user_data);

    typedef const osm_api_data_types::osm_relation * (*t_get_relation)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                       void * p_user_data);

    typedef const osm_api_data_types::osm_relation * (*t_get_relation_version)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                               const osm_api_data_types::osm_core_element::t_osm_version & p_version,
                                                                               void * p_user_data);

    typedef const std::vector<osm_api_data_types::osm_relation*> * const (*t_get_relation_history)(const osm_api_data_types::osm_object::t_osm_id & p_id,
												   void * p_user_data);

    typedef const std::vector<osm_api_data_types::osm_relation*> * const (*t_get_relation_relations)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                                                     void * p_user_data);

    typedef const osm_api_data_types::osm_relation * const (*t_get_relation_full)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                                  std::vector<osm_api_data_types::osm_node*> & p_nodes,
                                                                                  std::vector<osm_api_data_types::osm_way*> & p_ways,
                                                                                  void * p_user_data);

    typedef const std::vector<osm_api_data_types::osm_relation*> * const (*t_get_relations)(const std::vector<osm_api_data_types::osm_object::t_osm_id> & p_ids,
                                                                                            void * p_user_data);
    typedef const osm_api_data_types::osm_changeset* (*t_get_changeset)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                        void * p_user_data);

    typedef const std::vector<osm_api_data_types::osm_change*> * const (*t_get_changeset_content)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                                                  void * p_user_data);

    typedef const std::vector<osm_api_data_types::osm_changeset* > * const (*t_get_changesets)(const osm_api_data_types::osm_bounding_box & p_bounding_box,
                                                                                               const osm_api_data_types::osm_object::t_osm_id & p_id,
                                                                                               const std::string & p_user_name,
                                                                                               const std::string & p_time1,
                                                                                               const std::string & p_time2,
                                                                                               bool p_open,
                                                                                               bool p_close,
                                                                                               void * p_user_data);
    typedef void (*t_get_map)(const osm_api_data_types::osm_bounding_box & p_bounding_box,
                              std::vector<osm_api_data_types::osm_node*> & p_nodes,
                              std::vector<osm_api_data_types::osm_way*> & p_ways,
                              std::vector<osm_api_data_types::osm_relation*> & p_relations,
                              void *p_user_data);
    typedef void (*t_cache_node)(const osm_api_data_types::osm_node & p_node);
    typedef void (*t_cache_way)(const osm_api_data_types::osm_way & p_way);
    typedef void (*t_cache_relation)(const osm_api_data_types::osm_relation & p_relation);
    typedef void (*t_cache_user)(const osm_api_data_types::osm_object::t_osm_id & p_id,
                                 const std::string & p_user_name,
				 const osm_api_data_types::osm_object::t_osm_id & p_latest_changeset,
                                 const std::string & p_date);
    typedef const std::vector<osm_api_data_types::osm_change*> * const (*t_get_osm_change_file_content)(const std::string & p_file_name);
    typedef void (*t_get_osm_file_content)(const std::string & p_file_name,
					   std::vector<osm_api_data_types::osm_node*> & p_nodes,
					   std::vector<osm_api_data_types::osm_way*> & p_ways,
					   std::vector<osm_api_data_types::osm_relation*> & p_relations);

    typedef void (*t_get_user_browse_url)(std::string & p_result,
                                          const osm_api_data_types::osm_object::t_osm_id & p_id,
                                          const std::string & p_user_name);
    typedef void (*t_get_object_browse_url)(std::string & p_result,
                                            const std::string & p_type,
                                            const osm_api_data_types::osm_object::t_osm_id & p_id);
    typedef void (*t_get_api_object_url)(std::string & p_result,
                                         const std::string & p_type,
                                         const osm_api_data_types::osm_object::t_osm_id & p_id,
                                         const osm_api_data_types::osm_core_element::t_osm_version & p_version);

    typedef void (*t_ui_register_module)(const osm_diff_analyzer_if::analyzer_base & p_module,
					 const std::string & p_name);

    typedef void (*t_ui_append_log_text)(const osm_diff_analyzer_if::analyzer_base & p_module,
					 const std::string & p_text);

    typedef void (*t_ui_declare_html_report)(const osm_diff_analyzer_if::analyzer_base & p_module,
					     const std::string & p_name);

    typedef enum /* class */ {GET_API_VERSION=0,
			      GET_USER_SUBSCRIPTION_DATE,
                              GET_NODE,
			      GET_NODE_VERSION,
			      GET_NODE_HISTORY,
                              GET_NODE_WAYS,
                              GET_NODE_RELATIONS,
			      GET_NODES,
			      GET_WAY,
			      GET_WAY_VERSION,
			      GET_WAY_HISTORY,
			      GET_WAY_RELATIONS,
                              GET_WAY_FULL,
			      GET_WAYS,
			      GET_RELATION,
			      GET_RELATION_VERSION,
			      GET_RELATION_HISTORY,
			      GET_RELATION_RELATIONS,
                              GET_RELATION_FULL,
                              GET_RELATIONS,
                              GET_CHANGESET,
                              GET_CHANGESET_CONTENT,
                              GET_CHANGESETS,
                              GET_MAP,
			      CACHE_NODE,
			      CACHE_WAY,
			      CACHE_RELATION,
                              CACHE_USER,
			      GET_OSM_CHANGE_FILE_CONTENT,
                              GET_OSM_FILE_CONTENT,
                              GET_USER_BROWSE_URL,
                              GET_OBJECT_BROWSE_URL,
                              GET_API_OBJECT_URL,
			      UI_REGISTER_MODULE,
    			      UI_APPEND_LOG_TEXT,
			      UI_DECLARE_HTML_REPORT} t_common_api_index;
  };
}
#endif // _COMMON_API_IF_H_
//EOF
