#!/bin/sh
QUICKY_TOOLS=${PWD}/..
export QUICKY_TOOLS
QUICKY_OS=`uname -a | cut -d" " -f1`
export QUICKY_OS
PATH=${PATH}:${QUICKY_TOOLS}/bin
export PATH
#EOF