#!/bin/bash
read -p "String1: " str1
read -p "String2: " str2
 
# if with single square brackets and single =
if [ "$str1" = "$str2" ]	 
 
then
        echo "The strings are equal."
else
        echo "The strings are NOT equal."
fi
 
# if with double square brackets and ==
if [[ $str1 == $str2 ]] 
then
        echo "The strings are equal."
else
        echo "The strings are not equal."
fi

if [[ "$str1" != "$str2" ]];then  
        echo "The strings are not equal."
fi
