#!/bin/bash

#mkdir jyoti
if [ ! -d "files" ]; then
mkdir files
fi
cd files
#calculate last char if / exit
str=$1
last_char=$((${#str}-1))
echo $last_char
v=${str:$last_char:1}

[[ $v =~ "/" ]] && exit || echo not
#echo running
arr=$(echo $1 | tr "/" "\n")
arr_len=0
for x in $arr
do
   
    let "arr_len++"
done


i=0
for x in $arr
do
if [ $i == $(($arr_len -1)) ]; then
        touch $x
    else
        if [ ! -d $x ]; then
            mkdir $x
        fi
        cd $x
    fi
    let "i++"
done
