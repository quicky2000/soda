#!/bin/sh
cd ../..
mkdir run
mkdir run/batch_soda_analyzer_node_alignment
cp -rf examples/soda_analyzer_node_alignment/*  run/batch_soda_analyzer_node_alignment
cp -rf release/soda_batch/bin/* run/batch_soda_analyzer_node_alignment 
cd run/batch_soda_analyzer_node_alignment
./soda_batch.exe
firefox alignment_detector_node_alignment_report.html


