#!/bin/sh
cd ../..
mkdir run
mkdir run/GUI_soda_analyzer_war_room
cp -rf examples/soda_analyzer_war_room/*  run/GUI_soda_analyzer_war_room
cp -rf release/soda_QtUi/bin/* run/GUI_soda_analyzer_war_room
cd run/GUI_soda_analyzer_war_room
./soda_QtUi.exe

