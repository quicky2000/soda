cd ..\..
mkdir run
mkdir run\batch_soda_analyzer_war_room
copy examples\soda_analyzer_war_room\*  run\batch_soda_analyzer_war_room
xcopy release\soda_batch\* run\batch_soda_analyzer_war_room /E
copy release\soda_analyzer_war_room\bin\SDL.dll run\batch_soda_analyzer_war_room
cd run\batch_soda_analyzer_war_room
.\bin\soda_batch.exe france.conf
pause

