cd ..\..
mkdir run
mkdir run\batch_soda_analyzer_new_user
copy examples\soda_analyzer_new_user\*  run\batch_soda_analyzer_new_user
xcopy release\soda_batch\* run\batch_soda_analyzer_new_user /E
cd run\batch_soda_analyzer_new_user
.\bin\soda_batch.exe
explorer new_user.html
pause

