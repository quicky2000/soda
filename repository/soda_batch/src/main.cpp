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
#include <iostream>
#include <cstdlib>

int main(int p_argc,char ** p_argv)
{
  std::cout << "Nb arguments : " << p_argc << std::endl ;
  std::string l_file_name("");
  if(p_argc > 2)
    {
      std::cout << "ERROR : correct usage is osm_diff_watcher.exe [configuration_file_name]" << std::endl ;
      exit(EXIT_FAILURE);
    }
  if(p_argc == 2)
    {
      l_file_name = p_argv[1];
    }

  soda_batch::soda_text_Ui l_user_interface;
  l_user_interface.run(l_file_name);
}

//EOF
