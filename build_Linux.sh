## Prepare environment
#----------------------
cd repository
 . setup.sh

# Prepare build
#----------------
cd ..
mkdir build
cd build
mkdir soda_batch
cd soda_batch
generate_makefile soda_batch
make
cd ..
mkdir soda_QtUi
cd soda_QtUi
generate_makefile soda_QtUi
make

cd ..
mkdir soda_analyzer_key_survey
cd soda_analyzer_key_survey
generate_makefile soda_analyzer_key_survey
make library

cd ..
mkdir soda_analyzer_new_user
cd soda_analyzer_new_user
generate_makefile soda_analyzer_new_user
make library

cd ..
mkdir soda_analyzer_node_alignment
cd soda_analyzer_node_alignment
generate_makefile soda_analyzer_node_alignment
make library

cd ..
mkdir soda_analyzer_test_api
cd soda_analyzer_test_api
generate_makefile soda_analyzer_test_api
make library

cd ..
mkdir soda_analyzer_test_dom
cd soda_analyzer_test_dom
generate_makefile soda_analyzer_test_dom
make library

cd ..
mkdir soda_analyzer_user_data_dump
cd soda_analyzer_user_data_dump
generate_makefile soda_analyzer_user_data_dump
make library

cd ..
mkdir soda_analyzer_user_object
cd soda_analyzer_user_object
generate_makefile soda_analyzer_user_object
make library

cd ..
mkdir soda_analyzer_war_room
cd soda_analyzer_war_room
generate_makefile soda_analyzer_war_room
make library


cd ../..
ln -s build release
