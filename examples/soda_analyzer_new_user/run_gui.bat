cd ..\..
mkdir run
mkdir run\GUI_soda_analyzer_new_user
copy examples\soda_analyzer_new_user\*  run\GUI_soda_analyzer_new_user
xcopy release\soda_QtUi\* run\GUI_soda_analyzer_new_user /E
cd run\GUI_soda_analyzer_new_user
.\soda_QtUi.exe
pause

