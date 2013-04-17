cd ..\..
mkdir run
mkdir run\GUI_soda_analyzer_node_alignment
copy examples\soda_analyzer_node_alignment\*  run\GUI_soda_analyzer_node_alignment
xcopy release\soda_QtUi\* run\GUI_soda_analyzer_node_alignment /E
cd run\GUI_soda_analyzer_node_alignment
.\soda_QtUi.exe

