// Name: Awni AlQuraini
// Date: 11/18/2026
// Title: Lab 8 - Part 3
// Description: A C program that reads the files created in Step 1 using a provided byte buffer size
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Usage: %s <file name> <buffer size>\n", argv[0]);
        return 0;
    }

    uint8_t buffer[atoi(argv[2])];
    FILE *fp;
    fp = fopen(argv[1], "rb");

    if(fp == NULL){
        printf("File failed to open. Aborting...\n");
        return 1;
    }

    while(fread(buffer, 1, sizeof(buffer), fp)){}

    fclose(fp);
    printf("Successfully read file.\n");
}