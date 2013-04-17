cd ..\..
mkdir run
mkdir run\GUI_soda_analyzer_test_dom
copy examples\soda_analyzer_test_dom\*  run\GUI_soda_analyzer_test_dom
xcopy release\soda_QtUi\* run\GUI_soda_analyzer_test_dom /E
cd run\GUI_soda_analyzer_test_dom
.\soda_QtUi.exe

