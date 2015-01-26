#!/bin/bash
cd w3schools
#mkdir jyoti

arr=$(echo $1 | tr "/" "\n")
arr_len=0
for x in $arr
do
    let "arr_len++"
done

#echo $arr_len
i=0
for x in $arr
do
if [ $i == $(($arr_len -1)) ]; then
        touch $x
    else
        if [ ! -f $x ]; then
            mkdir $x
        fi
        cd $x
    fi
    let "i++"
done
