#!/bin/bash

# iterating over a list of strings
for os in Ubuntu CentOs Slackware "Kali Linux"
do
        echo "os is $os"
done

# iterating over a list of numbers
for num in {3..7}
do      
        echo "num is $num"
done 

# interating over a list of numbers in increments
for x in {10..100..5} 
do
        echo $x
done


# iterating over a list of files
for item in ./* # files in the current dir
do
	if [[ -f $item ]]
	then
		echo "Displaying the contents of $item"
		sleep 1
		cat $item
		echo "#######################"
	fi
done


# C/Java style
for ((i = 0 ; i <= 50 ; i++))
do
  echo "i = $i"
done
