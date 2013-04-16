#!/bin/sh
cd ../..
mkdir run
mkdir run/batch_soda_analyzer_user_object
cp -rf examples/soda_analyzer_user_object/*  run/batch_soda_analyzer_user_object
cp -rf release/soda_batch/bin/* run/batch_soda_analyzer_user_object
cd run/batch_soda_analyzer_user_object
./soda_batch.exe
firefox Geogast_object_report.html


