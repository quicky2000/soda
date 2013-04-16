#!/bin/sh
cd ../..
mkdir run
mkdir run/GUI_soda_analyzer_test_dom
cp -rf examples/soda_analyzer_test_dom/*  run/GUI_soda_analyzer_test_dom
cp -rf release/soda_QtUi/bin/* run/GUI_soda_analyzer_test_dom
cd run/GUI_soda_analyzer_test_dom
./soda_QtUi.exe

