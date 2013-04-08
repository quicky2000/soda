/*
    This file is part of osm_diff_analyzer_test_api, Openstreetmap
    diff analyzer whose aim is to test API allowing to analyzers to get
    OSM object information through OSM API implementation provided by
    diff analyzis framewwork
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
#include "test_api_analyzer.h"
#include "common_api.h"
#include "quicky_exception.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cassert>

namespace osm_diff_analyzer_test_api
{
  //------------------------------------------------------------------------------
  test_api_analyzer::test_api_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf,common_api & p_api):
    osm_diff_analyzer_sax_if::sax_analyzer_base("test_api",p_conf->get_name(),""),
    m_api(p_api),
    m_done(false)
  {
    // Register module to be able to use User Interface
    m_api.ui_register_module(*this,get_name());    
  }

  //------------------------------------------------------------------------------
  test_api_analyzer::~test_api_analyzer(void)
  {
  }

  //------------------------------------------------------------------------------
  void test_api_analyzer::init(const osm_diff_analyzer_if::osm_diff_state * p_diff_state)
  {
    {
      std::stringstream l_stream;
      l_stream << "Starting analyze of diff " << p_diff_state->get_sequence_number() ;
      m_api.ui_append_log_text(*this,l_stream.str());
    }
    if(!m_done)
      {
        m_done = true;
        // Get Node
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET Node 474827214");
        m_api.ui_append_log_text(*this,"========================");
        const osm_api_data_types::osm_node * l_node = m_api.get_node(474827214);
	if(l_node == NULL) throw quicky_exception::quicky_logic_exception("Unable to get node 474827214",__LINE__,__FILE__);
	
	{
	  std::stringstream l_stream;
	  l_stream << *l_node ; 
	  m_api.ui_append_log_text(*this,l_stream.str());
	}
        delete l_node;
        m_api.ui_append_log_text(*this,"------------------------");

        // Get Node version
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET Node 474827214 version 1");
        m_api.ui_append_log_text(*this,"========================");
        l_node = m_api.get_node_version(474827214,1);
	if(l_node == NULL) throw quicky_exception::quicky_logic_exception("Unable to get version 1 of node 474827214",__LINE__,__FILE__);

	{
	  std::stringstream l_stream;
	  l_stream << *l_node ; 
	  m_api.ui_append_log_text(*this,l_stream.str());
	}

        m_api.cache(*l_node);
        delete l_node;
        m_api.ui_append_log_text(*this,"------------------------");
   
        // Get Node history
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET Node 474827214 history");
        m_api.ui_append_log_text(*this,"========================");
        const std::vector<osm_api_data_types::osm_node *> * const l_node_history = m_api.get_node_history(474827214);
	
	if(NULL == l_node_history) throw quicky_exception::quicky_logic_exception("Unable to get history of node 474827214",__LINE__,__FILE__);

        for(std::vector<osm_api_data_types::osm_node *>::const_iterator l_iter = l_node_history->begin();
            l_iter != l_node_history->end();
            ++l_iter)
          {
            m_api.ui_append_log_text(*this,"-------------------------------");
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << *(*l_iter)  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        delete l_node_history;
        m_api.ui_append_log_text(*this,"------------------------");
   
        // Get all ways for a node shared by Rue des martyrs and Rampe provisoire
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET ways using Node 1947164927");
        m_api.ui_append_log_text(*this,"========================");
        const std::vector<osm_api_data_types::osm_way *> * const l_ways = m_api.get_node_ways(1947164927);

	if(NULL == l_ways) throw quicky_exception::quicky_logic_exception("Unable to get ways using node 1947164927",__LINE__,__FILE__);

        for(std::vector<osm_api_data_types::osm_way *>::const_iterator l_iter = l_ways->begin();
            l_iter != l_ways->end();
            ++l_iter)
          {
            m_api.ui_append_log_text(*this,"-------------------------------");
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << *(*l_iter)  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        delete l_ways;

        // Get all relations using bus stop victor hugo
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET relations using Node 1829038636");
        m_api.ui_append_log_text(*this,"========================");
        const std::vector<osm_api_data_types::osm_relation *> * const l_node_relations = m_api.get_node_relations(1829038636);

	if(NULL == l_node_relations) throw quicky_exception::quicky_logic_exception("Unable to get relations using node 1829038636",__LINE__,__FILE__);

        for(std::vector<osm_api_data_types::osm_relation *>::const_iterator l_iter = l_node_relations->begin();
            l_iter != l_node_relations->end();
            ++l_iter)
          {
            m_api.ui_append_log_text(*this,"-------------------------------");
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << *(*l_iter)  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        delete l_node_relations;

        // Get list of nodes
        std::vector<osm_api_data_types::osm_object::t_osm_id> l_node_ids;
        l_node_ids.push_back(344567058);
        l_node_ids.push_back(474827214);
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET Nodes (344567058,474827214)");
        m_api.ui_append_log_text(*this,"========================");
        const std::vector<osm_api_data_types::osm_node*> * l_list_node = m_api.get_nodes(l_node_ids);

	if(NULL == l_list_node) throw quicky_exception::quicky_logic_exception("Unable to get Nodes (344567058,474827214)",__LINE__,__FILE__);

        for(std::vector<osm_api_data_types::osm_node*>::const_iterator l_iter = l_list_node->begin();
            l_iter != l_list_node->end();
            ++l_iter)
          {
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << **l_iter  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        delete l_list_node;
        m_api.ui_append_log_text(*this,"------------------------");

        // Get way version
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET way 173118043");
        m_api.ui_append_log_text(*this,"========================");
        const osm_api_data_types::osm_way * l_way = m_api.get_way(173118043);
        if(NULL == l_way) throw quicky_exception::quicky_logic_exception("Unable to get way 173118043",__LINE__,__FILE__);

        {
	  std::stringstream l_stream;
	  l_stream << *l_way  ; 
	  m_api.ui_append_log_text(*this,l_stream.str());
	}
        delete l_way;
        m_api.ui_append_log_text(*this,"------------------------");
 
        // Get way version
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET way 173118043  version 1");
        m_api.ui_append_log_text(*this,"========================");
        l_way = m_api.get_way_version(173118043,1);
        if(NULL == l_way) throw quicky_exception::quicky_logic_exception("Unable to get version 1 of way 173118043",__LINE__,__FILE__);

        {
	  std::stringstream l_stream;
	  l_stream << *l_way  ; 
	  m_api.ui_append_log_text(*this,l_stream.str());
	}
        m_api.cache(*l_way);
        delete l_way;
        m_api.ui_append_log_text(*this,"------------------------");
 
        // Get Way history
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET Way 173118043 history");
        m_api.ui_append_log_text(*this,"========================");
        const std::vector<osm_api_data_types::osm_way *> * const l_way_history = m_api.get_way_history(173118043);

	if(NULL == l_way_history) throw quicky_exception::quicky_logic_exception("Unable to get history of way 173118043",__LINE__,__FILE__);

        for(std::vector<osm_api_data_types::osm_way *>::const_iterator l_iter = l_way_history->begin();
            l_iter != l_way_history->end();
            ++l_iter)
          {
            m_api.ui_append_log_text(*this,"-------------------------------");
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << *(*l_iter)  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        delete l_way_history;
        m_api.ui_append_log_text(*this,"------------------------");
   
        // Get all relations using way Rampe Provisoire
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET Relations using Way 184257352");
        m_api.ui_append_log_text(*this,"========================");
        const std::vector<osm_api_data_types::osm_relation *> * const l_way_relations = m_api.get_way_relations(184257352);

	if(NULL == l_way_relations) throw quicky_exception::quicky_logic_exception("Unable to get relations using Way 184257352",__LINE__,__FILE__);

        for(std::vector<osm_api_data_types::osm_relation *>::const_iterator l_iter = l_way_relations->begin();
            l_iter != l_way_relations->end();
            ++l_iter)
          {
            m_api.ui_append_log_text(*this,"-------------------------------");
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << *(*l_iter)  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        delete l_way_relations;
        m_api.ui_append_log_text(*this,"--------------------------------");

        // Get full way
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET full Way 173118043");
        m_api.ui_append_log_text(*this,"========================");
        std::vector<osm_api_data_types::osm_node*> l_way_nodes;
        const osm_api_data_types::osm_way * l_full_way = m_api.get_way_full(173118043,l_way_nodes);
        if(NULL == l_full_way) throw quicky_exception::quicky_logic_exception("Unable to get full way 173118043",__LINE__,__FILE__);

        {
	  std::stringstream l_stream;
	  l_stream << *l_full_way  ; 
	  m_api.ui_append_log_text(*this,l_stream.str());
	}
        for(std::vector<osm_api_data_types::osm_node*>::const_iterator l_iter = l_way_nodes.begin();
            l_iter != l_way_nodes.end();
            ++l_iter)
          {
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << **l_iter  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        delete l_full_way;
        m_api.ui_append_log_text(*this,"--------------------------------");

        m_api.ui_append_log_text(*this,"--------------------------------");
        // Get list of ways
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET Ways(173118043,184257352)");
        m_api.ui_append_log_text(*this,"========================");
        std::vector<osm_api_data_types::osm_object::t_osm_id> l_way_ids;
        l_way_ids.push_back(173118043);
        l_way_ids.push_back(184257352);
        const std::vector<osm_api_data_types::osm_way*> * l_list_way = m_api.get_ways(l_way_ids);

	if(NULL == l_list_way) throw quicky_exception::quicky_logic_exception("Unable to get ways(173118043,184257352)",__LINE__,__FILE__);

        for(std::vector<osm_api_data_types::osm_way*>::const_iterator l_iter = l_list_way->begin();
            l_iter != l_list_way->end();
            ++l_iter)
          {
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << **l_iter ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        delete l_list_way;
        m_api.ui_append_log_text(*this,"------------------------");

        // Get relation for bus line 30
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET relation 216546");
        m_api.ui_append_log_text(*this,"========================");
        const osm_api_data_types::osm_relation * l_relation = m_api.get_relation(216546);
        if(NULL == l_relation) throw quicky_exception::quicky_logic_exception("Unable to get relation 216546",__LINE__,__FILE__);

        {
	  std::stringstream l_stream;
	  l_stream << * l_relation  ;
	  m_api.ui_append_log_text(*this,l_stream.str());
	}
        delete l_relation;

        // Get relation for bus line 30
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET relation 216546 version 1");
        m_api.ui_append_log_text(*this,"========================");
        l_relation = m_api.get_relation_version(216546,1);
	
	if(NULL == l_relation) throw quicky_exception::quicky_logic_exception("Unable to get version 1 of relation 216546",__LINE__,__FILE__);

        {
	  std::stringstream l_stream;
	  l_stream << * l_relation  ;
	  m_api.ui_append_log_text(*this,l_stream.str());
	}
        m_api.cache(*l_relation);
        delete l_relation;

        // Get Relation history
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET Relation 216546 history");
        m_api.ui_append_log_text(*this,"========================");
        const std::vector<osm_api_data_types::osm_relation *> * const l_relation_history = m_api.get_relation_history(216546);

	if(NULL == l_relation_history) throw quicky_exception::quicky_logic_exception("Unable to get history of relation 216546",__LINE__,__FILE__);

        for(std::vector<osm_api_data_types::osm_relation *>::const_iterator l_iter = l_relation_history->begin();
            l_iter != l_relation_history->end();
            ++l_iter)
          {
            m_api.ui_append_log_text(*this,"-------------------------------");
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << *(*l_iter)  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        delete l_relation_history;
        m_api.ui_append_log_text(*this,"------------------------");
   
        // Get full relation for bus line 30
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET full Relation 216546");
        m_api.ui_append_log_text(*this,"========================");
        std::vector<osm_api_data_types::osm_node*> l_relation_nodes;
        std::vector<osm_api_data_types::osm_way*> l_relation_ways;
        const osm_api_data_types::osm_relation * l_full_relation = m_api.get_relation_full(216546,l_relation_nodes,l_relation_ways);

	if(NULL == l_full_relation) throw quicky_exception::quicky_logic_exception("Unable to get full relation 216546",__LINE__,__FILE__);

        {
	  std::stringstream l_stream;
	  l_stream << * l_full_relation  ;
	  m_api.ui_append_log_text(*this,l_stream.str());
	}
        delete l_full_relation;
        for(std::vector<osm_api_data_types::osm_node*>::const_iterator l_iter = l_relation_nodes.begin();
            l_iter != l_relation_nodes.end();
            ++l_iter)
          {
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << **l_iter  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        for(std::vector<osm_api_data_types::osm_way*>::const_iterator l_iter = l_relation_ways.begin();
            l_iter != l_relation_ways.end();
            ++l_iter)
          {
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << **l_iter  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        m_api.ui_append_log_text(*this,"--------------------------------");

        // Get list of relations
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET Relations(216546,191189)");
        m_api.ui_append_log_text(*this,"========================");
        std::vector<osm_api_data_types::osm_object::t_osm_id> l_relation_ids;
        l_relation_ids.push_back(216546);
        l_relation_ids.push_back(191189);
        const std::vector<osm_api_data_types::osm_relation*> * l_list_relation = m_api.get_relations(l_relation_ids);

	if(NULL == l_list_relation) throw quicky_exception::quicky_logic_exception("Unable to get relations 216546,191189",__LINE__,__FILE__);

        for(std::vector<osm_api_data_types::osm_relation*>::const_iterator l_iter = l_list_relation->begin();
            l_iter != l_list_relation->end();
            ++l_iter)
          {
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << **l_iter  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        delete l_list_relation;
        m_api.ui_append_log_text(*this,"------------------------");

        // Get changeset
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET changeset 13369487");
        m_api.ui_append_log_text(*this,"========================");
        const osm_api_data_types::osm_changeset * l_changeset = m_api.get_changeset(13369487);

	if(NULL == l_changeset) throw quicky_exception::quicky_logic_exception("Unable to get changeset 13369487",__LINE__,__FILE__);

        {
	  std::stringstream l_stream;
	  l_stream << *l_changeset  ;
	  m_api.ui_append_log_text(*this,l_stream.str());
	}
        delete l_changeset;
        m_api.ui_append_log_text(*this,"------------------------");

        // Get changeset content
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET changeset content 13369487");
        m_api.ui_append_log_text(*this,"========================");
        const std::vector<osm_api_data_types::osm_change *> * l_changes = m_api.get_changeset_content(13369487);

	if(NULL == l_changes) throw quicky_exception::quicky_logic_exception("Unable to get content of changeset  13369487",__LINE__,__FILE__);

        for(std::vector<osm_api_data_types::osm_change*>::const_iterator l_iter = l_changes->begin();
            l_iter != l_changes->end();
            ++l_iter)
          {
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << **l_iter  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        delete l_changes;
        m_api.ui_append_log_text(*this,"------------------------");

        // Get changesets of quicky
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET changesets of quicky since 2012-09-07T14:02:41Z");
        m_api.ui_append_log_text(*this,"========================");
        const std::vector<osm_api_data_types::osm_changeset*> * l_list_changeset = m_api.get_changesets(osm_api_data_types::osm_bounding_box(),0,"quicky","2012-09-07T14:02:41Z","",false,false);

	if(NULL == l_list_changeset) throw quicky_exception::quicky_logic_exception("Unable to get changesets of quicky since 2012-09-07T14:02:41Z",__LINE__,__FILE__);

        for(std::vector<osm_api_data_types::osm_changeset*>::const_iterator l_iter = l_list_changeset->begin();
            l_iter != l_list_changeset->end();
            ++l_iter)
          {
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << **l_iter  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        delete l_list_changeset;
        m_api.ui_append_log_text(*this,"------------------------");

        //Get map elements
        m_api.ui_append_log_text(*this,"========================");
        m_api.ui_append_log_text(*this,"GET map objects from (5.7076801,45.1925595,5.7112314,45.2000492)");
        m_api.ui_append_log_text(*this,"========================");
        std::vector<osm_api_data_types::osm_node*> l_map_nodes;
        std::vector<osm_api_data_types::osm_way*> l_map_ways;
        std::vector<osm_api_data_types::osm_relation*> l_map_relations;
        m_api.get_map(osm_api_data_types::osm_bounding_box(5.7076801,45.1925595,5.7112314,45.2000492),l_map_nodes,l_map_ways,l_map_relations);
        for(std::vector<osm_api_data_types::osm_node*>::const_iterator l_iter = l_map_nodes.begin();
            l_iter != l_map_nodes.end();
            ++l_iter)
          {
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << **l_iter  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        for(std::vector<osm_api_data_types::osm_way*>::const_iterator l_iter = l_map_ways.begin();
            l_iter != l_map_ways.end();
            ++l_iter)
          {
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << **l_iter  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        for(std::vector<osm_api_data_types::osm_relation*>::const_iterator l_iter = l_map_relations.begin();
            l_iter != l_map_relations.end();
            ++l_iter)
          {
            {
	      std::stringstream l_stream;
	      if(NULL == *l_iter) throw quicky_exception::quicky_logic_exception("*l_iter should not be NULL",__LINE__,__FILE__);
	      l_stream << **l_iter  ;
	      m_api.ui_append_log_text(*this,l_stream.str());
	    }
            delete *l_iter;
          }
        m_api.ui_append_log_text(*this,"------------------------");
      }
  }

  //------------------------------------------------------------------------------
  void test_api_analyzer::start_element(const std::string & p_name)
  {
  }

  //------------------------------------------------------------------------------
  void test_api_analyzer::end_element(const std::string & p_name)
  {
  }

  //------------------------------------------------------------------------------
  void test_api_analyzer::get_attribute(const std::string & p_name,const std::string & p_value)
  {
  }

  //------------------------------------------------------------------------------
  const std::string & test_api_analyzer::get_input_type(void)const
  {
    return m_description.get_input_type();
  }

  //------------------------------------------------------------------------------
  const std::string & test_api_analyzer::get_output_type(void)const
  {
    return m_description.get_output_type();
  }

  //------------------------------------------------------------------------------
  const std::string & test_api_analyzer::get_type(void)const
  {
    return m_description.get_type();
  }

  test_api_analyzer_description test_api_analyzer::m_description;
}
//EOF
