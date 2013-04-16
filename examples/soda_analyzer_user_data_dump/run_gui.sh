#!/bin/sh
cd ../..
mkdir run
mkdir run/GUI_soda_analyzer_user_data_dump
cp -rf examples/soda_analyzer_user_data_dump/*  run/GUI_soda_analyzer_user_data_dump
cp -rf release/soda_QtUi/bin/* run/GUI_soda_analyzer_user_data_dump
cd run/GUI_soda_analyzer_user_data_dump
./soda_QtUi.exe

