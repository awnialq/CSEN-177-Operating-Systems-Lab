#!/bin/bash
make;
echo "----------FIFO----------"
cat testInput.txt | ./pageReplacement 10 FIFO
echo "----------End FIFO----------"
echo
echo "----------LRU----------"
cat testInput.txt | ./pageReplacement 10 LRU
echo "----------End LRU----------"
echo
echo "----------Second Chance----------"
cat testInput.txt | ./pageReplacement 10 SECOND
echo "----------End Second Chance----------"
echo "FIFO 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./pageReplacement 10 FIFO | wc -l
cat accesses.txt | ./pageReplacement 50 FIFO | wc -l
cat accesses.txt | ./pageReplacement 100 FIFO | wc -l
cat accesses.txt | ./pageReplacement 250 FIFO | wc -l
cat accesses.txt | ./pageReplacement 500 FIFO | wc -l
echo
echo "LRU 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./pageReplacement 10 LRU | wc -l
cat accesses.txt | ./pageReplacement 50 LRU | wc -l
cat accesses.txt | ./pageReplacement 100 LRU | wc -l
cat accesses.txt | ./pageReplacement 250 LRU | wc -l
cat accesses.txt | ./pageReplacement 500 LRU | wc -l
echo
echo "Second Chance 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./pageReplacement 10 SECOND | wc -l
cat accesses.txt | ./pageReplacement 50 SECOND | wc -l
cat accesses.txt | ./pageReplacement 100 SECOND | wc -l
cat accesses.txt | ./pageReplacement 250 SECOND | wc -l
cat accesses.txt | ./pageReplacement 500 SECOND | wc -l
echo
make clean;
echo