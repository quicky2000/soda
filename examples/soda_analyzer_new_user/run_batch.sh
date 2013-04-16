#!/bin/sh
cd ../..
mkdir run
mkdir run/batch_soda_analyzer_new_user
cp -rf examples/soda_analyzer_new_user/*  run/batch_soda_analyzer_new_user
cp -rf release/soda_batch/bin/* run/batch_soda_analyzer_new_user
cd run/batch_soda_analyzer_new_user
./soda_batch.exe
firefox new_user.html


