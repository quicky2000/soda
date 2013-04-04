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
#include "soda_text_Ui.h"
#include "analyzer_base.h"
#include "osm_diff_watcher.h"
#include "quicky_exception.h"

#include <signal.h>

namespace soda_batch
{
  //----------------------------------------------------------------------------
  soda_text_Ui::soda_text_Ui(void):
    m_progress_min(0),
    m_progress_max(0)
  {
#ifndef _WIN32
    //Preparing signal handling to manage stop
    /* Déclaration d'une structure pour la mise en place des gestionnaires */
    struct sigaction l_signal_action;
  
    /* Remplissage de la structure pour la mise en place des gestionnaires */
    /* adresse du gestionnaire */
    l_signal_action.sa_handler=sig_handler;
    // Mise a zero du champ sa_flags theoriquement ignoré
    l_signal_action.sa_flags=0;
    /* On ne bloque pas de signaux spécifiques */
    sigemptyset(&l_signal_action.sa_mask);
    
    /* Mise en place du gestionnaire bidon pour trois signaux */
    sigaction(SIGINT,&l_signal_action,0);
#else
    signal(SIGINT,sig_handler);
#endif
  }

  //----------------------------------------------------------------------------
  void soda_text_Ui::run(const std::string & p_file_name)
  {
    try
      {
        m_watcher= new osm_diff_watcher::osm_diff_watcher(p_file_name,*this);
        m_watcher->run();
      }
    catch(quicky_exception::quicky_runtime_exception & e)
      {
        std::stringstream l_stream;
#ifdef SODA_QTUI_DEBUG
         l_stream << " from line " << e.get_line() << " in file " << e.get_file();
#endif
         std::cout << "ERROR : Runtime exception : " << std::string(e.what()) + l_stream.str() << std::endl;
      }
      catch(quicky_exception::quicky_logic_exception & e)
      {
          std::stringstream l_stream;
#ifdef SODA_QTUI_DEBUG
          l_stream << " from line " << e.get_line() << " in file " << e.get_file();
#endif
          std::cout << "ERROR : Logic exception : "<< std::string(e.what())/* + l_stream.str()*/ << std::endl;
      }
      catch(std::logic_error & e)
      {
          std::cout << "ERROR : Logic error"<< std::string(e.what())<< std::endl;
      }
      catch(std::runtime_error & e)
      {
          std::cout << "ERROR : Runtime error"<< std::string(e.what())<< std::endl;
      }
    delete m_watcher;
    m_watcher = NULL;
  }

  //------------------------------------------------------------------------------
  void soda_text_Ui::sig_handler(int p_sig)
  {
    std::cout << "===================> Receive Control-C : execution will stop after this minute diff analyze will be finished" << std::endl ;
    if(m_watcher)m_watcher->stop();
  }

  // Methods inherited from soda_Ui_if
  // General communication
  //------------------------------------------------------------------------------
  void soda_text_Ui::clear_common_text()
  {
    // Nothing to do in a text Ui
  }

  //------------------------------------------------------------------------------
  void soda_text_Ui::append_common_text(const std::string & p_text)
  {
    std::cout << p_text << std::endl ;
  }

  //------------------------------------------------------------------------------
  void soda_text_Ui::update_diff_state(const osm_diff_analyzer_if::osm_diff_state & p_diff_state)
  {
    std::cout << "Sequence number : " << p_diff_state.get_sequence_number() << "\tTimestamp of diff file : " << p_diff_state.get_timestamp() << std::endl ;
  }

  //------------------------------------------------------------------------------
  void soda_text_Ui::instantiate_module(const std::string & p_name,const osm_diff_analyzer_if::analyzer_base & p_module)
  {
    std::cout << "Creation of module \"" << p_name << "\"" << std::endl ;
  }

  // Module communication
  //------------------------------------------------------------------------------
  void soda_text_Ui::append_log_text(const osm_diff_analyzer_if::analyzer_base & p_module,
				     const std::string & p_text)
  {
    std::cout << p_module.get_name() << " : " << p_text << std::endl ;
  }

  //------------------------------------------------------------------------------
  void soda_text_Ui::declare_html_report(const osm_diff_analyzer_if::analyzer_base & p_module,
					 const std::string & p_text)
  {
  }

  //------------------------------------------------------------------------------
  void soda_text_Ui::configure_progress_display(const unsigned int & p_min, const unsigned int & p_max)
  {
    m_progress_min = p_min;
    m_progress_max = p_max;
  }

  //------------------------------------------------------------------------------
  void soda_text_Ui::update_progress(const unsigned int & p_value)
  {
    if(m_progress_max)
      {
	std::cout << "Progress : " << 100.0*((float)(p_value - m_progress_min))/((float)m_progress_max) << "%" << std::endl ;
      }
  }

  // End of methods inherited from soda_Ui_if
  osm_diff_watcher::osm_diff_watcher * soda_text_Ui::m_watcher = NULL;


}
//EOF
