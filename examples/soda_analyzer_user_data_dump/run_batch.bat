cd ..\..
mkdir run
mkdir run\batch_soda_analyzer_user_data_dump
copy examples\soda_analyzer_user_data_dump\*  run\batch_soda_analyzer_user_data_dump
xcopy release\soda_batch\* run\batch_soda_analyzer_user_data_dump /E
cd run\batch_soda_analyzer_user_data_dump
.\bin\soda_batch.exe
pause

