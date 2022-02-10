#!/bin/bash
cd /opt/P600
loop_flag=true
while $loop_flag
do
    result=`ps -ef | grep -w P600 | grep -v grep | wc -l`
    if [ $result -le 0 ]; then
        ./P600.sh
    else
        pid=`ps -aux | grep P600 | grep -v grep | awk '{print $2}'`
        #kill -9 $pid
	sleep 2
        ./P600.sh
    fi
done
