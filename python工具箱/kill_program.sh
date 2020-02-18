#!/bin/sh

PROGRAM=$2
USER=$1

function show_help()
{
   echo "$0 user program"
}


if [ ! -n "$1" ] ;then
    show_help
    exit
fi

if [ "$PROGRAM" = "" ];then
    show_help
    exit
fi

echo $PROGRAM
echo $USER

PID=`ps -ef | grep $USER | grep $PROGRAM | grep -v $0 | grep -v grep | awk '{print $2}'`
echo $PID
echo "---------------"
for id in $PID
do
#kill -9 $id
echo "killed $id"
done
echo "---------------"
