#!/bin/sh
cd ../..
mkdir run
mkdir run/GUI_soda_analyzer_key_survey
cp -rf examples/soda_analyzer_key_survey/*  run/GUI_soda_analyzer_key_survey
cp -rf release/soda_QtUi/bin/* run/GUI_soda_analyzer_key_survey 
cd run/GUI_soda_analyzer_key_survey
./soda_QtUi.exe


