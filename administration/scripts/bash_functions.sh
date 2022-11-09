#!/bin/bash

# defining a function: method 1
function print_something () {  .
        echo "I'm a simple function!"
}
 
# defining a function: method 2
display_something () {
        echo "Hello functions!"
}
# either of the above methods of specifying a function is valid. 

create_files () {
        echo "Create $1"
        touch $1
        chmod 400 $1
        return 10
}

function lines_in_file () {
        grep -c "$1" "$2"
}

# calling the functions 
print_something
display_something
create_files ducndc.txt
echo ?$ 

n=$(lines_in_file "usb" "/var/log/kern.log")
echo $n