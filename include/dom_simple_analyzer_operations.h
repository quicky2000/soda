#ifndef _DOM_SIMPLE_ANALYZER_OPERATIONS_H_
#define _DOM_SIMPLE_ANALYZER_OPERATIONS_H_

#include "dom_simple_analyzer_if.h"

namespace osm_diff_watcher
{
  class apply_simple_init: public analyze_operation<dom_simple_analyzer_if>
  {
  public:
    void operator()(dom_simple_analyzer_if * p_analyzer)const
    {
      p_analyzer->init();
    }
  }
  ;

 class dom_simple_analyze_operation: public analyze_operation<dom_simple_analyzer_if>
  {
  public:
    dom_simple_analyze_operation(const osm_diff_analyzer_dom_if::t_dom_tree & p_tree):
      m_tree(p_tree)
      {
      }

      void operator()(dom_simple_analyzer_if * p_analyzer)const
      {
	p_analyzer->analyze(m_tree);
      }
  private:
      const osm_diff_analyzer_dom_if::t_dom_tree & m_tree;
  }
  ;
}
#endif
//EOF
