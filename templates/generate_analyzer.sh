#! /bin/sh
#-------------------------------------------------------------------------------
#    This file is a generator of empty soda analyzer
#    Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>
#-------------------------------------------------------------------------------

# First parameter is the suffix use to determine the name of the module to be created : soda-analyzer_<suffix>
# Second parameter is the type of module to generate : sax, dom or cpp
echo "------------------------"
echo "Name of analyzer : $1"
echo "Type of module : $2"
echo "------------------------"
mkdir soda_analyzer_${1}
mkdir soda_analyzer_${1}/include
mkdir soda_analyzer_${1}/src
cp ${2}_analyzer/infra_infos.txt soda_analyzer_${1}/
sed -e "s/NAME/${1}/g" common/include/NAME_analyzer_description.h > soda_analyzer_${1}/include/${1}_analyzer_description.h
sed -e "s/NAME/${1}/g" ${2}_analyzer/include/NAME_analyzer.h > soda_analyzer_${1}/include/${1}_analyzer.h
sed -e "s/NAME/${1}/g" common/include/NAME_common_api.h > soda_analyzer_${1}/include/${1}_common_api.h
sed -e "s/NAME/${1}/g" common/include/NAME_wrapper.h > soda_analyzer_${1}/include/${1}_wrapper.h
sed -e "s/NAME/${1}/g" ${2}_analyzer/src/NAME_analyzer.cpp > soda_analyzer_${1}/src/${1}_analyzer.cpp
sed -e "s/NAME/${1}/g" ${2}_analyzer/src/NAME_analyzer_description.cpp > soda_analyzer_${1}/src/${1}_analyzer_description.cpp
sed -e "s/NAME/${1}/g" common/src/NAME_wrapper.cpp > soda_analyzer_${1}/src/${1}_wrapper.cpp

echo "=> Module generated"
#EOF
