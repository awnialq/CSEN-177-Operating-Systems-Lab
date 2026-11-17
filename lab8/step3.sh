#!/bin/bash
gcc step3.c -o step3
for file in file1.txt file2.txt file3.txt file4.txt 
do
	for buffer in 100 1000 10000 100000
	do
		echo "File name: $file | Buffer size: $buffer"
		time ./step3 $file $buffer
		echo " "
	done
done
