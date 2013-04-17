#!/bin/sh
# Clean repository
root=${PWD}
echo "-> Clean directories"
rm -rf MinGW_repository build
# Generate MinGW repository
echo "-> Generate MinGW repository"
mkdir MinGW_repository
cp repository/setup.sh MinGW_repository
cp -rf repository/quicky_tools MinGW_repository
echo "# Prepare repository for soda_batch"
# Prepare repository for soda_batch
mkdir MinGW_repository/soda_batch
mkdir MinGW_repository/soda_batch/include
mkdir MinGW_repository/soda_batch/src
cp repository/soda_batch/include/* MinGW_repository/soda_batch/include
cp repository/soda_batch/src/* MinGW_repository/soda_batch/src
cp repository/soda_core/include/* MinGW_repository/soda_batch/include
cp repository/soda_core/src/* MinGW_repository/soda_batch/src
cp MinGW_material/soda_batch/infra_infos.txt MinGW_repository/soda_batch
cp repository/soda_analyzer_if/include/* MinGW_repository/soda_batch/include
cp repository/soda_analyzer_sax_if/include/* MinGW_repository/soda_batch/include
cp repository/soda_analyzer_dom_if/include/* MinGW_repository/soda_batch/include
cp repository/quicky_exception/include/* MinGW_repository/soda_batch/include
cp repository/soda_analyzer_cpp_if/include/* MinGW_repository/soda_batch/include
cp repository/EXT_gzstream/include/* MinGW_repository/soda_batch/include
cp repository/EXT_gzstream/src/* MinGW_repository/soda_batch/src
cp repository/url_reader/include/* MinGW_repository/soda_batch/include
cp repository/url_reader/src/* MinGW_repository/soda_batch/src
cp repository/osm_api_data_types/include/* MinGW_repository/soda_batch/include
cp repository/osm_api_data_types/src/* MinGW_repository/soda_batch/src
cp repository/EXT_xmlParser/include/* MinGW_repository/soda_batch/include
cp repository/EXT_xmlParser/src/* MinGW_repository/soda_batch/src
cp repository/EXT_sqlite3/include/my_sqlite3.h MinGW_repository/soda_batch/include
cp MinGW_material/sqlite3/include/* MinGW_repository/soda_batch/include
cp -rf MinGW_material/libcurl/include/* MinGW_repository/soda_batch/include
cp -rf MinGW_material/zlib/include/* MinGW_repository/soda_batch/include
cp -rf MinGW_material/libexpat/include/*.h MinGW_repository/soda_batch/include


echo "# Prepare repository for soda_QtUi"
mkdir -p build/soda_QtUi/libs
cp MinGW_material/soda_QtUi/* build/soda_QtUi 
cp -rf MinGW_material/libcurl/lib/* build/soda_QtUi/libs
cp -rf MinGW_material/sqlite3/lib/* build/soda_QtUi/libs
cp -rf MinGW_material/libexpat/lib/* build/soda_QtUi/libs
cp -rf MinGW_material/zlib/lib/* build/soda_QtUi/libs
cp -rf MinGW_material/zlib/include/* build/soda_QtUi/
cp -rf MinGW_material/libcurl/include/* build/soda_QtUi
cp -rf MinGW_material/libexpat/include/* build/soda_QtUi
cp -rf MinGW_material/sqlite3/include/* build/soda_QtUi
cp repository/soda_QtUi/include/* build/soda_QtUi
cp repository/soda_QtUi/src/* build/soda_QtUi
cp repository/soda_core/include/* build/soda_QtUi
cp repository/soda_core/src/* build/soda_QtUi
cp repository/url_reader/include/* build/soda_QtUi
cp repository/url_reader/src/* build/soda_QtUi
cp repository/EXT_xmlParser/include/* build/soda_QtUi
cp repository/EXT_xmlParser/src/* build/soda_QtUi
cp repository/EXT_gzstream/include/* build/soda_QtUi
cp repository/EXT_sqlite3/include/* build/soda_QtUi
cp repository/EXT_gzstream/src/* build/soda_QtUi
cp repository/osm_api_data_types/include/* build/soda_QtUi
cp repository/osm_api_data_types/src/* build/soda_QtUi
cp repository/soda_analyzer_cpp_if/include/* build/soda_QtUi
cp repository/soda_analyzer_sax_if/include/* build/soda_QtUi
cp repository/soda_analyzer_dom_if/include/* build/soda_QtUi
cp repository/soda_analyzer_if/include/* build/soda_QtUi
cp repository/quicky_exception/include/* build/soda_QtUi

echo "# Prepare repository for soda_analyzer_key_survey"
# Prepare repository for soda_analyzer_key_survey
mkdir MinGW_repository/soda_analyzer_key_survey
mkdir MinGW_repository/soda_analyzer_key_survey/include
mkdir MinGW_repository/soda_analyzer_key_survey/src
cp -rf MinGW_material/soda_analyzer_key_survey/infra_infos.txt MinGW_repository/soda_analyzer_key_survey/
cp -rf repository/soda_analyzer_key_survey/include/* MinGW_repository/soda_analyzer_key_survey/include
cp -rf repository/soda_analyzer_key_survey/src/* MinGW_repository/soda_analyzer_key_survey/src
cp repository/soda_analyzer_cpp_if/include/* MinGW_repository/soda_analyzer_key_survey/include
cp repository/soda_analyzer_if/include/* MinGW_repository/soda_analyzer_key_survey/include
cp repository/EXT_sqlite3/include/my_sqlite3.h MinGW_repository/soda_analyzer_key_survey/include
cp repository/osm_api_data_types/include/* MinGW_repository/soda_analyzer_key_survey/include
cp repository/osm_api_data_types/src/* MinGW_repository/soda_analyzer_key_survey/src
cp MinGW_material/sqlite3/include/* MinGW_repository/soda_analyzer_key_survey/include
cp repository/quicky_exception/include/* MinGW_repository/soda_analyzer_key_survey/include
echo "# Prepare repository for soda_analyzer_new_user"
# Prepare repository for soda_analyzer_new_user
mkdir MinGW_repository/soda_analyzer_new_user
mkdir MinGW_repository/soda_analyzer_new_user/include
mkdir MinGW_repository/soda_analyzer_new_user/src
cp -rf MinGW_material/soda_analyzer_new_user/infra_infos.txt MinGW_repository/soda_analyzer_new_user/
cp -rf repository/soda_analyzer_new_user/include/* MinGW_repository/soda_analyzer_new_user/include
cp -rf repository/soda_analyzer_new_user/src/* MinGW_repository/soda_analyzer_new_user/src
cp repository/soda_analyzer_sax_if/include/* MinGW_repository/soda_analyzer_new_user/include
cp repository/soda_analyzer_if/include/* MinGW_repository/soda_analyzer_new_user/include
cp repository/osm_api_data_types/include/* MinGW_repository/soda_analyzer_new_user/include
cp repository/osm_api_data_types/src/* MinGW_repository/soda_analyzer_new_user/src
cp repository/quicky_exception/include/* MinGW_repository/soda_analyzer_new_user/include
echo "# Prepare repository for soda_analyzer_node_alignment"
# Prepare repository for soda_analyzer_node_alignment
mkdir MinGW_repository/soda_analyzer_node_alignment
mkdir MinGW_repository/soda_analyzer_node_alignment/include
mkdir MinGW_repository/soda_analyzer_node_alignment/src
cp -rf MinGW_material/soda_analyzer_node_alignment/infra_infos.txt MinGW_repository/soda_analyzer_node_alignment/
cp -rf repository/soda_analyzer_node_alignment/include/* MinGW_repository/soda_analyzer_node_alignment/include
cp -rf repository/soda_analyzer_node_alignment/src/* MinGW_repository/soda_analyzer_node_alignment/src
cp repository/soda_analyzer_cpp_if/include/* MinGW_repository/soda_analyzer_node_alignment/include
cp repository/soda_analyzer_if/include/* MinGW_repository/soda_analyzer_node_alignment/include
cp repository/osm_api_data_types/include/* MinGW_repository/soda_analyzer_node_alignment/include
cp repository/osm_api_data_types/src/* MinGW_repository/soda_analyzer_node_alignment/src
cp repository/quicky_exception/include/* MinGW_repository/soda_analyzer_node_alignment/include
echo "# Prepare repository for soda_analyzer_test_api"
# Prepare repository for soda_analyzer_test_api
mkdir MinGW_repository/soda_analyzer_test_api
mkdir MinGW_repository/soda_analyzer_test_api/include
mkdir MinGW_repository/soda_analyzer_test_api/src
cp -rf MinGW_material/soda_analyzer_test_api/infra_infos.txt MinGW_repository/soda_analyzer_test_api/
cp -rf repository/soda_analyzer_test_api/include/* MinGW_repository/soda_analyzer_test_api/include
cp -rf repository/soda_analyzer_test_api/src/* MinGW_repository/soda_analyzer_test_api/src
cp repository/soda_analyzer_sax_if/include/* MinGW_repository/soda_analyzer_test_api/include
cp repository/soda_analyzer_if/include/* MinGW_repository/soda_analyzer_test_api/include
cp repository/osm_api_data_types/include/* MinGW_repository/soda_analyzer_test_api/include
cp repository/osm_api_data_types/src/* MinGW_repository/soda_analyzer_test_api/src
cp repository/quicky_exception/include/* MinGW_repository/soda_analyzer_test_api/include
echo "# Prepare repository for soda_analyzer_test_dom"
# Prepare repository for soda_analyzer_test_dom
mkdir MinGW_repository/soda_analyzer_test_dom
mkdir MinGW_repository/soda_analyzer_test_dom/include
mkdir MinGW_repository/soda_analyzer_test_dom/src
cp -rf MinGW_material/soda_analyzer_test_dom/infra_infos.txt MinGW_repository/soda_analyzer_test_dom/
cp -rf repository/soda_analyzer_test_dom/include/* MinGW_repository/soda_analyzer_test_dom/include
cp -rf repository/soda_analyzer_test_dom/src/* MinGW_repository/soda_analyzer_test_dom/src
cp repository/soda_analyzer_dom_if/include/* MinGW_repository/soda_analyzer_test_dom/include
cp repository/soda_analyzer_if/include/* MinGW_repository/soda_analyzer_test_dom/include
cp repository/EXT_xmlParser/include/* MinGW_repository/soda_analyzer_test_dom/include
cp repository/EXT_xmlParser/src/* MinGW_repository/soda_analyzer_test_dom/src
cp repository/osm_api_data_types/include/* MinGW_repository/soda_analyzer_test_dom/include
cp repository/osm_api_data_types/src/* MinGW_repository/soda_analyzer_test_dom/src
cp repository/quicky_exception/include/* MinGW_repository/soda_analyzer_test_dom/include
echo "# Prepare repository for soda_analyzer_user_data_dump"
# Prepare repository for soda_analyzer_user_data_dump
mkdir MinGW_repository/soda_analyzer_user_data_dump
mkdir MinGW_repository/soda_analyzer_user_data_dump/include
mkdir MinGW_repository/soda_analyzer_user_data_dump/src
cp -rf MinGW_material/soda_analyzer_user_data_dump/infra_infos.txt MinGW_repository/soda_analyzer_user_data_dump/
cp -rf repository/soda_analyzer_user_data_dump/include/* MinGW_repository/soda_analyzer_user_data_dump/include
cp -rf repository/soda_analyzer_user_data_dump/src/* MinGW_repository/soda_analyzer_user_data_dump/src
cp repository/soda_analyzer_sax_if/include/* MinGW_repository/soda_analyzer_user_data_dump/include
cp repository/soda_analyzer_if/include/* MinGW_repository/soda_analyzer_user_data_dump/include
cp repository/osm_api_data_types/include/* MinGW_repository/soda_analyzer_user_data_dump/include
cp repository/osm_api_data_types/src/* MinGW_repository/soda_analyzer_user_data_dump/src
cp repository/quicky_exception/include/* MinGW_repository/soda_analyzer_user_data_dump/include
echo "# Prepare repository for soda_analyzer_user_object"
# Prepare repository for soda_analyzer_user_object
mkdir MinGW_repository/soda_analyzer_user_object
mkdir MinGW_repository/soda_analyzer_user_object/include
mkdir MinGW_repository/soda_analyzer_user_object/src
cp -rf MinGW_material/soda_analyzer_user_object/infra_infos.txt MinGW_repository/soda_analyzer_user_object/
cp -rf repository/soda_analyzer_user_object/include/* MinGW_repository/soda_analyzer_user_object/include
cp -rf repository/soda_analyzer_user_object/src/* MinGW_repository/soda_analyzer_user_object/src
cp repository/soda_analyzer_cpp_if/include/* MinGW_repository/soda_analyzer_user_object/include
cp repository/soda_analyzer_if/include/* MinGW_repository/soda_analyzer_user_object/include
cp repository/EXT_sqlite3/include/my_sqlite3.h MinGW_repository/soda_analyzer_user_object/include
cp repository/osm_api_data_types/include/* MinGW_repository/soda_analyzer_user_object/include
cp repository/osm_api_data_types/src/* MinGW_repository/soda_analyzer_user_object/src
cp MinGW_material/sqlite3/include/* MinGW_repository/soda_analyzer_user_object/include
cp repository/quicky_exception/include/* MinGW_repository/soda_analyzer_user_object/include
echo "# Prepare repository for soda_analyzer_war_room"
# Prepare repository for soda_analyzer_war_room
mkdir MinGW_repository/soda_analyzer_war_room
mkdir MinGW_repository/soda_analyzer_war_room/include
mkdir MinGW_repository/soda_analyzer_war_room/src
cp -rf MinGW_material/soda_analyzer_war_room/infra_infos.txt MinGW_repository/soda_analyzer_war_room/
cp -rf repository/soda_analyzer_war_room/include/* MinGW_repository/soda_analyzer_war_room/include
cp -rf repository/soda_analyzer_war_room/src/* MinGW_repository/soda_analyzer_war_room/src
cp -rf MinGW_material/libsdl/include/* MinGW_repository/soda_analyzer_war_room/include
cp -rf repository/simple_gui/include/* MinGW_repository//soda_analyzer_war_room/include
cp -rf repository/simple_gui/src/* MinGW_repository//soda_analyzer_war_room/src
cp -rf repository/lib_bmp/include/* MinGW_repository//soda_analyzer_war_room/include
cp repository/soda_analyzer_sax_if/include/* MinGW_repository/soda_analyzer_war_room/include
cp repository/soda_analyzer_if/include/* MinGW_repository/soda_analyzer_war_room/include
cp repository/osm_api_data_types/include/* MinGW_repository/soda_analyzer_war_room/include
cp repository/osm_api_data_types/src/* MinGW_repository/soda_analyzer_war_room/src
cp repository/quicky_exception/include/* MinGW_repository/soda_analyzer_war_room/include
# Prepare environment
echo "-> Prepare environment"
cd MinGW_repository
repository=${PWD}
. setup.sh
cd $root
# Prepare build
echo "-> Prepare build"
mkdir build
cd build
build_root=${PWD}
# Build soda_analyzer_key_survey
echo "-> Build soda_analyzer_key_survey"
mkdir $build_root/soda_analyzer_key_survey && cd $build_root/soda_analyzer_key_survey
generate_makefile soda_analyzer_key_survey
cp -rf $root/MinGW_material/sqlite3/lib/* .
make library
cd $build_root
# Build soda_analyzer_new_user
echo "-> Build soda_analyzer_new_user"
mkdir $build_root/soda_analyzer_new_user && cd $build_root/soda_analyzer_new_user
generate_makefile soda_analyzer_new_user
make library
cd $build_root
# Build soda_analyzer_node_alignment
echo "-> Build soda_analyzer_node_alignment"
mkdir $build_root/soda_analyzer_node_alignment && cd $build_root/soda_analyzer_node_alignment
generate_makefile soda_analyzer_node_alignment
make library
cd $build_root
# Build soda_analyzer_test_api
echo "-> Build soda_analyzer_test_api"
mkdir $build_root/soda_analyzer_test_api && cd $build_root/soda_analyzer_test_api
generate_makefile soda_analyzer_test_api
make library
cd $build_root
# Build soda_analyzer_test_dom
echo "-> Build soda_analyzer_test_dom"
mkdir $build_root/soda_analyzer_test_dom && cd $build_root/soda_analyzer_test_dom
generate_makefile soda_analyzer_test_dom
make library
cd $build_root
# Build soda_analyzer_user_data_dump
echo "-> Build soda_analyzer_user_data_dump"
mkdir $build_root/soda_analyzer_user_data_dump && cd $build_root/soda_analyzer_user_data_dump
generate_makefile soda_analyzer_user_data_dump
make library
cd $build_root
# Build soda_analyzer_user_object
echo "-> Build soda_analyzer_user_object"
mkdir $build_root/soda_analyzer_user_object && cd $build_root/soda_analyzer_user_object
generate_makefile soda_analyzer_user_object
cp -rf $root/MinGW_material/sqlite3/lib/* .
make library
cd $build_root
# Build soda_analyzer_war_room
echo "-> Build soda_analyzer_war_room"
mkdir $build_root/soda_analyzer_war_room && cd $build_root/soda_analyzer_war_room
generate_makefile soda_analyzer_war_room
cp -rf $root/MinGW_material/libsdl/lib/* .
make library
cd $build_root

# Build soda_batch
echo "-> Build soda_batch"
mkdir $build_root/soda_batch && cd $build_root/soda_batch 
generate_makefile soda_batch
cp -rf $root/MinGW_material/libcurl/lib/* .
cp -rf $root/MinGW_material/sqlite3/lib/* .
cp -rf $root/MinGW_material/libexpat/lib/* .
cp -rf $root/MinGW_material/zlib/lib/* .
make

cd $root

