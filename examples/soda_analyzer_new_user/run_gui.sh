#!/bin/sh
cd ../..
mkdir run
mkdir run/GUI_soda_analyzer_new_user
cp -rf examples/soda_analyzer_new_user/*  run/GUI_soda_analyzer_new_user
cp -rf release/soda_QtUi/bin/* run/GUI_soda_analyzer_new_user
cd run/GUI_soda_analyzer_new_user
./soda_QtUi.exe


