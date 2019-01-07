#!/bin/sh
#pstack 13951 >> log.time 2>&1
nohup strace -o out.txt -T -tt -e trace=all -p 13951 & 2>&1
#ps -ef  |grep "scf test1 1" | grep -u antl | grep -v grep | awk '{print $2}' | xargs -i nohup strace -o out.txt -T -tt -e trace=all -p {} &
#ps -ef  | grep "scf test1 1" | grep -u antl | grep -v grep | awk '{print $2}' | xargs -i pstack {} >> log.time 2>&1
#pstack 13951 >> log.time 2>&1
#ps -ef  | grep "scf test1 1" | grep -u antl | grep -v grep | awk '{print $2}' | xargs -i pstack {} >> log.time 2>&1
echo "eeeeeeeeeeeeeeee" >> log.time
count=0
while [ true ]; do
    sleep 1
    time=$(date "+%Y-%m-%d %H:%M:%S")
    timestamp=`date -d "$time" +%s`
    echo "time:${time}  timestamp:${timestamp}" >> log.time
 #   ps -ef  | grep "scf test1 1" | grep -u antl | grep -v grep | awk '{print $2}' | xargs -i pstack {} >> log.time 2>&1 
    pstack 13951 >> out.txt 2>&1
    count=$(($count+1))
    echo "count:${count}"
    if [ $count -gt 3 ]
    then
        break
    fi
done

#ps -ef  | grep pstack | grep -u antl | grep -v grep | awk '{print $2}' | xargs -i kill {}
ps -ef  | grep strace | grep -u antl | grep -v grep | awk '{print $2}' | xargs -i kill {}
