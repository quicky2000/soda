#!/bin/sh
cd ../..
mkdir run
mkdir run/batch_soda_analyzer_test_api
cp -rf examples/soda_analyzer_test_api/*  run/batch_soda_analyzer_test_api
cp -rf release/soda_batch/bin/* run/batch_soda_analyzer_test_api
cd run/batch_soda_analyzer_test_api
./soda_batch.exe


