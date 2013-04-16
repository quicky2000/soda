#!/bin/sh
mkdir tmp_package
cp -rf build_Linux.sh doc LICENCE README repository examples tmp_package
cd tmp_package
tar -zcvf soda.tar.gz *
mv soda.tar.gz ..
cd ..
rm -rf tmp_package


