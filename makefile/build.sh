#!/bin/bash

#OS type
os_type=$(uname)
echo -e '\E[32m' "OS type:" $os_type

echo "The command is $0"

echo "start make file"
make -f make.mk
echo "makefile code $?"
