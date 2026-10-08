#!/bin/bash
# Removes the 50 test files created by make_test_files.sh.
for i in $(seq -w 1 50); do
	rm -f "testfile_$i.txt"
done
echo "Removed 50 test files."
