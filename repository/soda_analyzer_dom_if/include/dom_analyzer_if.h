/*
    This file is part of osm_diff_analyzer_dom_if, Interface definitions 
    of DOM based Openstreetmap diff analyzers
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
#ifndef _DOM_ANALYZER_IF_H_
#define _DOM_ANALYZER_IF_H_

#include "dom_analyzer_generic_if.h"
#include "diff_analyzer_if.h"
#include "dom_tree.h"

namespace osm_diff_analyzer_dom_if
{
  class dom_analyzer_if: public osm_diff_analyzer_if::diff_analyzer_if, public dom_analyzer_generic_if<XMLNode>
  {
    public:
    virtual void analyze(const XMLNode & p_tree)=0;
    inline virtual ~dom_analyzer_if(void){};
  };
}

#endif // _DOM_ANALYZER_IF_H_
//EOF
