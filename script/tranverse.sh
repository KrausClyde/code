#!/bin/bash

#tranverse folder
function tranverseFolder()
{
    echo "tranverse folder"
    echo "$0 $1 $2 $3"
    flist=$(ls)

    for f in ${flist}
    do
        if test -d $f
        then
            echo "folder $f"
            cd $f
            tranverseFolder $f
            cd ..
        else
            echo "file $f"
        fi
    done
}

function changeName(){
    #new=`echo $1|sed 's/^/abc/g'`
    new=`echo $1|sed -r 's/abc(.*$)/\1/g'`
    #echo $new
    mv $1 $new
}
#a=$(ls)  
#echo "$a"

dir=/mnt/hgfs/vmshared
echo "current dir: dir pwd:$(pwd)"
tranverseFolder ${dir}

#sed -i 's/Old/New/g' ${filename}

