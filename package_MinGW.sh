#!/bin/sh
root=${PWD}
build_root=$root/build
mkdir $root/release
mkdir -p $root/release/soda_batch/bin
mkdir -p $root/release/soda_QtUi/bin
mkdir -p $root/release/soda_analyzer_key_survey/bin
mkdir -p $root/release/soda_analyzer_new_user/bin
mkdir -p $root/release/soda_analyzer_node_alignment/bin
mkdir -p $root/release/soda_analyzer_test_api/bin
mkdir -p $root/release/soda_analyzer_test_dom/bin
mkdir -p $root/release/soda_analyzer_user_data_dump/bin
mkdir -p $root/release/soda_analyzer_user_object/bin
mkdir -p $root/release/soda_analyzer_war_room/bin
cp $build_root/soda_batch/*.dll $root/release/soda_batch/
cp $build_root/soda_batch/bin/soda_batch.exe $root/release/soda_batch/bin/
cp $build_root/soda_QtUi/libs/*.dll $root/release/soda_QtUi/bin
cp $root/MinGW_material/Qt_libs/*.dll $root/release/soda_QtUi/bin
cp $build_root/soda_QtUi/release/soda_QtUi.exe $root/release/soda_QtUi/bin/
cp $build_root/soda_analyzer_key_survey/bin/libsoda_analyzer_key_survey.so $root/release/soda_analyzer_key_survey/bin/
cp $build_root/soda_analyzer_new_user/bin/libsoda_analyzer_new_user.so $root/release/soda_analyzer_new_user/bin/
cp $build_root/soda_analyzer_node_alignment/bin/libsoda_analyzer_node_alignment.so $root/release/soda_analyzer_node_alignment/bin/
cp $build_root/soda_analyzer_test_api/bin/libsoda_analyzer_test_api.so $root/release/soda_analyzer_test_api/bin/
cp $build_root/soda_analyzer_test_dom/bin/libsoda_analyzer_test_dom.so $root/release/soda_analyzer_test_dom/bin/
cp $build_root/soda_analyzer_user_data_dump/bin/libsoda_analyzer_user_data_dump.so $root/release/soda_analyzer_user_data_dump/bin/
cp $build_root/soda_analyzer_user_object/bin/libsoda_analyzer_user_object.so $root/release/soda_analyzer_user_object/bin/
cp $build_root/soda_analyzer_war_room/bin/libsoda_analyzer_war_room.so $root/release/soda_analyzer_war_room/bin/
cp -rf $root/MinGW_material/libsdl/lib/* $root/release/soda_analyzer_war_room/bin/
tar -zcvf soda_win32_binaries.tar.gz release README examples 
tar -zcvf soda_win32_build.tar.gz README MinGW_material repository build_MinGW.sh examples

