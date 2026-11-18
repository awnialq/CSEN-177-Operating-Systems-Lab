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
    snprintf(out, sizeof(out), "write_out_%d.out", (args->id + 1));
    FILE *reader;
    FILE *writer;

    reader = fopen(args->fname, "rb");
    if(reader == NULL){
        printf("Thread %d: File failed to open. Aborting...\n", args->id);
        return NULL;
    }

    writer = fopen(out, "wb");
    if(writer == NULL){
        printf("Thread %d: Failed to creater writer file. Aborting...\n", args->id);
        fclose(reader);
        return NULL;
    }

    size_t n;
    while((n = fread(buffer, 1, sizeof(buffer), reader))){
        fwrite(buffer, 1, n, writer);
    }

    fclose(reader);
    fclose(writer);
    return NULL;
}

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("Usage: %s <file name> <buffer size> <# of threads>\n", argv[0]);
        return 0;
    }

    int num_threads = atoi(argv[3]);
    int buf_size = atoi(argv[2]);

    struct thread_arg *t_args = malloc(num_threads * sizeof(struct thread_arg));

    pthread_t threads[num_threads];
    for(int i = 0; i < num_threads; ++i){
        t_args[i].fname = argv[1];
        t_args[i].id = i;
        t_args[i].buffer_size = buf_size;
        pthread_create(&threads[i], NULL, writer_task, &t_args[i]);
    }

    for(int i = 0; i < num_threads; ++i){
        pthread_join(threads[i], NULL);
    }
    
    free(t_args);
    printf("Successfully executed.\n");
    return 0;
}