cd ..\..
mkdir run
mkdir run\batch_soda_analyzer_node_alignment
copy examples\soda_analyzer_node_alignment\*  run\batch_soda_analyzer_node_alignment
xcopy release\soda_batch\* run\batch_soda_analyzer_node_alignment /E
cd run\batch_soda_analyzer_node_alignment
.\bin\soda_batch.exe
explorer alignment_detector_node_alignment_report.html
pause

