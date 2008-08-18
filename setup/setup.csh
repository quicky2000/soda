#!/bin/tcsh
setenv QUICKY_TOOLS ${PWD}/..
setenv QUICKY_OS `uname -a | cut -d" " -f1`
setenv PATH ${PATH}:${QUICKY_TOOLS}/bin
#EOF
