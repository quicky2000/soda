#ifndef _DOM_OSM_FULL_RELATION_EXTRACTOR_H_
#define _DOM_OSM_FULL_RELATION_EXTRACTOR_H_

#include "dom_simple_analyzer_if.h"
#include "dom_generic_utilities.h"
#include <cstring>

namespace osm_diff_watcher
{
  class dom_osm_full_relation_extractor: public dom_simple_analyzer_if
  {
  public:
    inline dom_osm_full_relation_extractor(std::vector<osm_api_data_types::osm_node*> & p_nodes,
					   std::vector<osm_api_data_types::osm_way*> & p_ways);
    // Method inherited from dom_analyzer_if
    inline void analyze(const osm_diff_analyzer_dom_if::t_dom_tree & p_tree);
    inline void init(void){}
    // end of Method inherited from dom_analyzer_if
    inline osm_api_data_types::osm_relation * get_result(void)const;
  private:
    std::vector<osm_api_data_types::osm_node*> & m_nodes;
    std::vector<osm_api_data_types::osm_way*> & m_ways;
    osm_api_data_types::osm_relation * m_result;
   
  };

  //----------------------------------------------------------------------------
  osm_api_data_types::osm_relation * dom_osm_full_relation_extractor::get_result(void)const
    {
      return m_result;
    }

  //----------------------------------------------------------------------------
  dom_osm_full_relation_extractor::dom_osm_full_relation_extractor(std::vector<osm_api_data_types::osm_node*> & p_nodes,
								   std::vector<osm_api_data_types::osm_way*> & p_ways):
    m_nodes(p_nodes),
    m_ways(p_ways),
    m_result(NULL)
  {
  }

  //----------------------------------------------------------------------------
  void dom_osm_full_relation_extractor::analyze(const osm_diff_analyzer_dom_if::t_dom_tree & p_tree)
  {
      assert(!strcmp("osm",p_tree.getName()));
      int l_nb_version = p_tree.nChildNode();
      for(int l_index = 0; l_index < l_nb_version ; ++l_index)
	{
	  osm_diff_analyzer_dom_if::t_dom_tree l_node = p_tree.getChildNode(l_index);
	  if(osm_api_data_types::osm_node::get_type_str() == l_node.getName())
	    {
	      m_nodes.push_back(generic_dom_utilities<osm_diff_analyzer_dom_if::t_dom_tree>::extract_info<osm_api_data_types::osm_node>(l_node,true));
	    }
	  else if(osm_api_data_types::osm_way::get_type_str() == l_node.getName())
	    {
	      m_ways.push_back(generic_dom_utilities<osm_diff_analyzer_dom_if::t_dom_tree>::extract_info<osm_api_data_types::osm_way>(l_node,true));
	    }
	  else if(osm_api_data_types::osm_relation::get_type_str() == l_node.getName())
	    {
	      m_result = generic_dom_utilities<osm_diff_analyzer_dom_if::t_dom_tree>::extract_info<osm_api_data_types::osm_relation>(l_node,true);
	    }
	  else
	    {
	      std::cout << "Unexpected node type \"" << l_node.getName() << "\"" << std::endl ;
	      exit(-1);
	    }
	}
  }
}
#endif // _DOM_OSM_FULL_RELATION_EXTRACTOR_H_
//EOF
