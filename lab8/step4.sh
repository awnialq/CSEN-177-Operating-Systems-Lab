#!/bin/bash
gcc step4.c -o step4
for file in file1.txt file2.txt file3.txt file4.txt 
do
	for buffer in 100 1000 10000 100000
	do
		echo "step4 $file $buffer"
		time ./step4 $file $buffer
		cmp $file write_dump.out
		echo " "
	done
done
rm write_dump.out