cd ..\..
mkdir run
mkdir run\GUI_soda_analyzer_user_object
copy examples\soda_analyzer_user_object\*  run\GUI_soda_analyzer_user_object
xcopy release\soda_QtUi\* run\GUI_soda_analyzer_user_object /E
cd run\GUI_soda_analyzer_user_object
.\soda_QtUi.exe
pause

