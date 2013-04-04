/*
  This file is part of soda_batch, text user interface for 
  Openstreetmap diff analyze framework.
  The aim of this software is to provided generic facilities for diff analyzis
  to allow developers to concentrate on analyze rather than diff management 
  infrastructure
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
#ifndef _SODA_TEXT_UI_H_
#define _SODA_TEXT_UI_H_

#include "soda_Ui_if.h"

namespace osm_diff_watcher
{
  class osm_diff_watcher;
}

namespace soda_batch
{
  class soda_text_Ui: public osm_diff_watcher::soda_Ui_if
  {
  public:
    soda_text_Ui(void);
    void run(const std::string & p_file_name);
    // Methods inherited from soda_Ui_General
    // if communication
    void clear_common_text();
    void append_common_text(const std::string & p_text);
    void update_diff_state(const osm_diff_analyzer_if::osm_diff_state & p_diff_state);
    void instantiate_module(const std::string & p_name,const osm_diff_analyzer_if::analyzer_base & p_module);
    void configure_progress_display(const unsigned int & p_min, const unsigned int & p_max);
    void update_progress(const unsigned int &);
    // Module communication
    void append_log_text(const osm_diff_analyzer_if::analyzer_base & p_module,
			 const std::string & p_text);
    void declare_html_report(const osm_diff_analyzer_if::analyzer_base & p_module,
			     const std::string & p_text);
    // End of methods inherited from soda_Ui_if
  private:
    unsigned int m_progress_min;
    unsigned int m_progress_max;
    static void sig_handler(int p_sig);
    static osm_diff_watcher::osm_diff_watcher * m_watcher;
  };
}

#endif // _SODA_TEXT_UI_H_
//EOF
