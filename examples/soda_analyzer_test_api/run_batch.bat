cd ..\..
mkdir run
mkdir run\batch_soda_analyzer_test_api
copy examples\soda_analyzer_test_api\*  run\batch_soda_analyzer_test_api
xcopy release\soda_batch\* run\batch_soda_analyzer_test_api /E
cd run\batch_soda_analyzer_test_api
.\bin\soda_batch.exe
pause

