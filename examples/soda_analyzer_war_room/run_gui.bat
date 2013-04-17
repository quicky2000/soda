cd ..\..
mkdir run
mkdir run\GUI_soda_analyzer_war_room
copy examples\soda_analyzer_war_room\*  run\GUI_soda_analyzer_war_room
xcopy release\soda_QtUi\* run\GUI_soda_analyzer_war_room /E
copy release\soda_analyzer_war_room\bin\SDL.dll run\GUI_soda_analyzer_war_room
cd run\GUI_soda_analyzer_war_room
.\soda_QtUi.exe

