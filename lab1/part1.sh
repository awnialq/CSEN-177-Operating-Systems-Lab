# Name: Awni AlQuraini
# Date: 09/23/2026
# Title: Lab 1 - Part 1 shell script
#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user='whoami'
numusers='who | wc -l'
echo "Hi $user! There are $numusers users logged on." 
