/*
  This file is part of soda_QtUi, Graphical User Interface
  of SODA ( Smart Openstreetmap Diff Analyzer )
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
#ifndef MODULE_LIST_TABLE_H
#define MODULE_LIST_TABLE_H

#include <QTableWidget>

namespace soda_QtUi
{
    class module_list_table: public QTableWidget
    {
    public:
        module_list_table(QWidget *parent=NULL);
        void add_module(const std::string & p_name,
			const std::string & p_type,
			bool p_enabled);
	void update_row(unsigned int p_row,
			const std::string & p_name,
			const std::string & p_type,
			bool p_enabled);
    private:
    };
}
#endif // MODULE_LIST_TABLE_H
