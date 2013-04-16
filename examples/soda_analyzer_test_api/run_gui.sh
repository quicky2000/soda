#!/bin/sh
cd ../..
mkdir run
mkdir run/GUI_soda_analyzer_test_api
cp -rf examples/soda_analyzer_test_api/*  run/GUI_soda_analyzer_test_api
cp -rf release/soda_QtUi/bin/* run/GUI_soda_analyzer_test_api
cd run/GUI_soda_analyzer_test_api
./soda_QtUi.exe

