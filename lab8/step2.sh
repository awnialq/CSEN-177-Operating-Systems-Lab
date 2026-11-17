#!/bin/bash
gcc step2.c -o step2
for file in file1.txt file2.txt file3.txt file4.txt 
do
	echo "File name: $file"
	time ./step2 $file
	echo " "
done
rm step2