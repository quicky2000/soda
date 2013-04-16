#!/bin/sh
cd ../..
mkdir run
mkdir run/GUI_soda_analyzer_user_object
cp -rf examples/soda_analyzer_user_object/*  run/GUI_soda_analyzer_user_object
cp -rf release/soda_QtUi/bin/* run/GUI_soda_analyzer_user_object
cd run/GUI_soda_analyzer_user_object
./soda_QtUi.exe
