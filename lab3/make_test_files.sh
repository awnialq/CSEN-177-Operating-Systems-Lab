#!/bin/bash
# Creates 50 small test files (testfile_01.txt ... testfile_50.txt) in the
# current directory so that `ls -l | more` in part1 has enough output to page.
for i in $(seq -w 1 50); do
	echo "This is test file number $i" > "testfile_$i.txt"
done
echo "Created 50 test files."
