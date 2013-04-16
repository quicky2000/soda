#!/bin/sh
cd ../..
mkdir run
mkdir run/GUI_soda_analyzer_node_alignment
cp -rf examples/soda_analyzer_node_alignment/*  run/GUI_soda_analyzer_node_alignment
cp -rf release/soda_QtUi/bin/* run/GUI_soda_analyzer_node_alignment
cd run/GUI_soda_analyzer_node_alignment
./soda_QtUi.exe

