// Name: Awni AlQuraini
// Date: 11/18/2026
// Title: Lab 8 - Part 4
// Description: A C program that reads the files created in Step 1 using a provided byte buffer size and writes the read to a new file
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Usage: %s <file name> <buffer size>\n", argv[0]);
        return 0;
    }

    uint8_t buffer[atoi(argv[2])];
    FILE *reader;
    FILE *writer;
    reader = fopen(argv[1], "rb");
    writer = fopen("write_dump.out", "wb");

    if(reader == NULL){
        printf("File failed to open. Aborting...\n");
        return 1;
    }

    if(writer == NULL){
        printf("Failed to creater writer file. Aborting...\n");
        return 1;
    }

    size_t n;
    while((n = fread(buffer, 1, sizeof(buffer), reader))){
        fwrite(buffer, 1, n, writer);
    }

    fclose(reader);
    fclose(writer);
    printf("Successfully executed.\n");
    return 0;
}