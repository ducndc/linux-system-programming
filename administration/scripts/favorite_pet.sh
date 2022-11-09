#!/bin/bash
echo -n "Enter your favorite pet:"
read PET

case "$PET" in 
	dog)
		echo "Your favorite pet is the dog"
		;;
	cat|Cat)
		echo "You like cats"
		;;
	fish|"Afirican Turtle")
		echo "Fish or tutles are great"
		;;
	*)
		echo "you do not know"
esac