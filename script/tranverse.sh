#!/bin/bash

#tranverse folder
function tranFolder()
{
    echo "tranverse folder"
    flist='ls $1'
    cd $1

    for f in $flist
    do
        if test -d $f
        then
            echo "$f"
            tranFolder $f
        else
            echo "$f"
        fi
    done
    cd ../
}

dir=(cd $(pwd)/..)
echo "current dir: $(dir) pwd:$(pwd)"
tranFolder ${dir}
