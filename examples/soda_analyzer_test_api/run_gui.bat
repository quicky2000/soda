cd ..\..
mkdir run
mkdir run\GUI_soda_analyzer_test_api
copy examples\soda_analyzer_test_api\*  run\GUI_soda_analyzer_test_api
xcopy release\soda_QtUi\* run\GUI_soda_analyzer_test_api /E
cd run\GUI_soda_analyzer_test_api
.\soda_QtUi.exe

