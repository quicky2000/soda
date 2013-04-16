#!/bin/sh
cd ../..
mkdir run
mkdir run/batch_soda_analyzer_war_room
cp -rf examples/soda_analyzer_war_room/*  run/batch_soda_analyzer_war_room
cp -rf release/soda_batch/bin/* run/batch_soda_analyzer_war_room
cd run/batch_soda_analyzer_war_room
./soda_batch.exe france.conf

