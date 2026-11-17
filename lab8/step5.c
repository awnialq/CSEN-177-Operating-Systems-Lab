// Name: Awni AlQuraini
// Date: 11/18/2026
// Title: Lab 8 - Part 5
// Description: A C program that reads the files created in Step 1 and makes multiple different copies using theads
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

struct thread_arg{
    char *fname;
    int buffer_size;
    int id;
};

void *writer_task(void *arg){
    struct thread_arg *args = arg;

    uint8_t buffer[args->buffer_size]; 
    char out[64];
    snprintf(out, sizeof(out), "write_out_%d.out", args->id);
    FILE *reader;
    FILE *writer;
    reader = fopen(args->fname, "rb");
    writer = fopen(out, "wb");

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
    return 0;
}

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("Usage: %s <file name> <buffer size> <# of threads>\n", argv[0]);
        return 0;
    }

    pthread_t threads[atoi(argv[3])];
    
    printf("Successfully executed.\n");
    return 0;
}