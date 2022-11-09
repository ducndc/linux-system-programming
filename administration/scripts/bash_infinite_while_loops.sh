#!/bin/bash

# creating an infinite loop
# while [ 1 -eq 1 ]  
# do
# 	echo "Infinite loop, press <CTRL+C> to exit."
# 	sleep 1
# done


# monitoring a process
while :  # equivalent to while true:
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

# Move to the script's directory and run it as: ./script_name.sh process_name