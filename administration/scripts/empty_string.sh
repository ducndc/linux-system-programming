#!/bin/bash

my_str=""

if [[ -z "$my_str" ]]
then
	echo "String is zero length"
else
	echo "String IS NOT zero length"
fi

if [[ -n "$my_str" ]]
then 
	echo "String is not zero length"
else
	echo "String is zero length"
fi