#!/bin/bash
i=0 
while [[ $i -lt 10 ]] 
do
	echo "i: $i"
    ((i++))     # same as: let i=i+1
done


# creating an infinite loop
while [ 1 -eq 1 ]  
do
	echo "Infinite loop, press <CTRL+C> to exit."
	sleep 1
done


while :
do
	output="$(pgrep -l $1)"
	if [[ -n "$output" ]]  
	then
		echo "The process \"$1\" is running."
	else
		echo "The process \"$1\" IS NOT running."
	fi	
	sleep 3 
done