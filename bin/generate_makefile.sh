#! /bin/sh
if [ -z $QUICKY_TOOLS ]
then echo "Environment variable QUICKY_TOOLS is not set"
exit 3
fi

if [ $# -eq 1 ]
then target_name=Makefile
input_name=Makefile.ref 
elif [ $# -eq 2 ]
then target_name=$2
input_name=sub_makefile.ref 
else echo "generate_makefile.sh <object_name> [ <output_file_name> ]"
exit 3
fi
sed -e "s/<to_be_defined>/${1}/g" ${QUICKY_TOOLS}/data/${input_name} > ${target_name} 
