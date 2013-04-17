cd ..\..
mkdir run
mkdir run\batch_soda_analyzer_key_survey
copy examples\soda_analyzer_key_survey\*  run\batch_soda_analyzer_key_survey
xcopy release\soda_batch\* run\batch_soda_analyzer_key_survey /E
cd run\batch_soda_analyzer_key_survey
.\bin\soda_batch.exe
explorer wikipedia_detailled_object_report.html
explorer wikipedia_object_report.html
pause

