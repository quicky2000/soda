cd ..\..
mkdir run
mkdir run\batch_soda_analyzer_test_dom
copy examples\soda_analyzer_test_dom\*  run\batch_soda_analyzer_test_dom
xcopy release\soda_batch\* run\batch_soda_analyzer_test_dom /E
cd run\batch_soda_analyzer_test_dom
.\bin\soda_batch.exe
pause

