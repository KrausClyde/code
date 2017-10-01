#!/bin/bash

#OS type
os_type=$(uname)
echo -e '\E[32m' "OS type:" $os_type

echo "start make file"
make -f makefile.mk
echo "makefile code $?"
