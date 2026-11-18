#!/bin/bash
echo "----------Running Make----------"
make all
echo "----------Listing Files----------"
ls -l file?.txt
echo "----------Running Steps----------"
echo "Step 2"
for file in file1.txt file2.txt file3.txt file4.txt
do
    TIMEFORMAT="step2 $file %R"
    time ./step2 $file > /dev/null
done
echo "Step 3"
for file in file1.txt file2.txt file3.txt file4.txt
do
    for buffer in 100 1000 10000 100000
    do
        TIMEFORMAT="step3 $file $buffer %R"
        time ./step3 $file $buffer > /dev/null
    done
done
echo "Step 4"
for file in file1.txt file2.txt file3.txt file4.txt
do
    for buffer in 100 1000 10000 100000
    do
        TIMEFORMAT="step4 $file $buffer %R"
        time ./step4 $file $buffer > /dev/null
    done
done
echo "Step 5"
for file in file1.txt file2.txt file3.txt file4.txt
do
    for buffer in 100 1000 10000 100000
    do
        for thread in 2 8 32 64
        do
            TIMEFORMAT="step5 $file $buffer $thread %R"
            time ./step5 $file $buffer $thread > /dev/null
        done
    done
done
echo "----------Cleaning Up----------"
make clean
