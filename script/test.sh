#!/bin/bash

echo "The command entered is : $0"

echo "There were $# parameters supplied"
echo "The last parameter is ${!#}"

count=1
for param in "$*"
do
	echo "\$* Parameter #$count = $param"
	count=$[ $count + 1 ]
done

count=1
for param in "$@"
do
	echo "\$@ Parameter #$count = $param"
	count=$[ $count + 1 ]
done
