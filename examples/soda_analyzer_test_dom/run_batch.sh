#!/bin/sh
cd ../..
mkdir run
mkdir run/batch_soda_analyzer_test_dom
cp -rf examples/soda_analyzer_test_dom/*  run/batch_soda_analyzer_test_dom
cp -rf release/soda_batch/bin/* run/batch_soda_analyzer_test_dom
cd run/batch_soda_analyzer_test_dom
./soda_batch.exe
