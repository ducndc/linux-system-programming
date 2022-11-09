#!/bin/bash
create_files () {
	echo "Creating $1"
	touch $1
	chmod 400 $1
 
	echo "Creating $2"
	touch $2
	chmod 600 $2
}

# calling the function with 2 args
create_files aa.txt bb.txt

# function that returns a valus (output of a command)
function lines_in_file() {
        grep -c "$1" "$2"
}

n=$(lines_in_file "usb" "/var/log/dmesg")
echo $n
