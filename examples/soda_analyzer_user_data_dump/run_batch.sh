#!/bin/sh
cd ../..
mkdir run
mkdir run/batch_soda_analyzer_user_data_dump
cp -rf examples/soda_analyzer_user_data_dump/*  run/batch_soda_analyzer_user_data_dump
cp -rf release/soda_batch/bin/* run/batch_soda_analyzer_user_data_dump 
cd run/batch_soda_analyzer_user_data_dump
./soda_batch.exe

