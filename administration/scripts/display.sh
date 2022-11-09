#!/bin/bash
if [[ $# -eq 1 ]]  
then 
	if [ -f "$1" ]
	then
		echo "The argument is a file, displaying its contents ..."
		sleep 1
		cat $1
	elif [ -d "$1" ]
	then 
		echo "The argument is a directory, running ls -l ..."
		sleep 1
		ls -l $1
	else
		echo "The argument ($1) is neither a file nor a directory."
	fi
else
	echo "The script should be run with an argument"
fi

# Move to the script's directory and run it as: ./script_name.sh filename|dirname