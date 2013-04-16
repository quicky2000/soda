#!/bin/sh
cd ../..
mkdir run
mkdir run/batch_soda_analyzer_key_survey
cp -rf examples/soda_analyzer_key_survey/*  run/batch_soda_analyzer_key_survey
cp -rf release/soda_batch/bin/* run/batch_soda_analyzer_key_survey 
cd run/batch_soda_analyzer_key_survey
./soda_batch.exe
firefox wikipedia_detailled_object_report.html
firefox wikipedia_object_report.html


