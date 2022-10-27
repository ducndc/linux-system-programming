# Challenges - File Permissions
# How to solve these challenges:

# To be consistent with the filenames and paths run the commands on Ubuntu

# Write your solution in a terminal and test it.

# If your solution is not correct, then try to understand the error messages, watch the video again, 
# rewrite the solution, and test it again. 
# Repeat this step until you get the correct solution.

# Save the solution in a file for future reference or recap.

# Create a directory with a regular file in it. Work as a non-privileged user.
mkdir linux
echo "This is Ubuntu" > linux/ubuntu.txt

# Challenge #1

# Display the permissions of ubuntu.txt

# Remove all permissions of others.
stat linux/ubuntu.txt
chmod 660 linux/ubuntu.txt

# Challenge #2

# Remove the read permission of ubuntu.txt for the owner 
# and check if the owner can read the file.
chmod 620 linux/ubuntu.txt

# Challenge #3

# Using the octal notation, set the permissions of 
# the directory to rwxrwx--- and of the file to rw-r-----
chmod 640 filename

# Challenge #4

# Set the permissions of the directory to 0667. 
# Check if the user (owner) can list its contents, 
# move to the directory and remove it.
chmod 0667 linux/

# Challenge #5

# Set the permissions of all the files in the user's home directory 
# to 0640 and the permissions of all directories to 0750.
chmod 0750 /home 

# Challenge #7

# Set the directory permissions to 0777 and the file permissions to 0000. 
# As another non-privileged user, try to remove the file.

# Create a new file in the directory and set its permissions to 0644.

# Set the Sticky Bit on the directory.

# As another non-privileged user, try to remove the file.
chmod +t /mydir

# Challenge #8

# Change the owner and the group owner of all files in 
# the current user home directory to the current user and its primary group.
