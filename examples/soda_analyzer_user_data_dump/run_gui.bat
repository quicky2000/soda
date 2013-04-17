cd ..\..
mkdir run
mkdir run\GUI_soda_analyzer_user_data_dump
copy examples\soda_analyzer_user_data_dump\*  run\GUI_soda_analyzer_user_data_dump
xcopy release\soda_QtUi\* run\GUI_soda_analyzer_user_data_dump /E
cd run\GUI_soda_analyzer_user_data_dump
.\soda_QtUi.exe

