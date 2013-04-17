cd ..\..
mkdir run
mkdir run\GUI_soda_analyzer_key_survey
copy examples\soda_analyzer_key_survey\*  run\GUI_soda_analyzer_key_survey
xcopy release\soda_QtUi\* run\GUI_soda_analyzer_key_survey /E
cd run\GUI_soda_analyzer_key_survey
.\soda_QtUi.exe
pause

