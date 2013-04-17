cd ..\..
mkdir run
mkdir run\batch_soda_analyzer_user_object
copy examples\soda_analyzer_user_object\*  run\batch_soda_analyzer_user_object
xcopy release\soda_batch\* run\batch_soda_analyzer_user_object /E
cd run\batch_soda_analyzer_user_object
.\bin\soda_batch.exe
explorer Geogast_object_report.html
pause

