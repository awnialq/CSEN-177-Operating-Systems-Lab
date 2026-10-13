// Name: Awni AlQuraini
// Date: 10/7/2026
// Title: Lab 4 - Part 3
// Description: A program showcasing a multi-threaded solution tasking each thread with the multiplication of a whole row
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

double **matA, **matB, **matC; //A, B, C matricies are global
int n, m, l;

double **allocMat(int r, int c){
    double **mat = malloc(r * sizeof(double *));
    if(mat == NULL){
        perror("malloc");
        exit(1);
    }
    for(int i = 0; i < r; i++){
        mat[i] = malloc(c * sizeof(double));
    }
    return mat;
}

void freeMat(double **mat, int r){
    for(int i = 0; i < r; i++){
        free(mat[i]);
    }
    free(mat);
}

void *initMat(double **mat, int r, int c){
    static int seeded = 0;
    if(!seeded){
        srand(time(NULL));
        seeded = 1;
    }
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            mat[i][j] = rand();
        }
    }
    return NULL;
}

void printMat(double **mat, int r, int c){
    for(int i = 0; i < r; i++){
        printf("\t");
        for(int j = 0; j < c; j++){
            printf("%f\t", mat[i][j]);
        }
        printf("\n");
    }
}

void *multRow(void *arg){
    int i = (int)(size_t) arg;
    for(int j = 0; j < l; j++){
        double temp = 0;
        for(int k = 0; k < m; k++){
            temp += matA[i][k] * matB[k][j];
        }
        matC[i][j] = temp;
    }
    return NULL;
}

int main(int argc, char *argv[]){
    if(argc != 4){
        printf("Usage: %s <value for n> <value for m> <value for l>\n", argv[0]);
        exit(0);
    }

    n = atoi(argv[1]);
    m = atoi(argv[2]);
    l = atoi(argv[3]);

    if(n <= 0 || m <= 0 || l <= 0){
        printf("n, m, and l must be positive integers\n");
        exit(1);
    }

    pthread_t threads[n];
    matA = allocMat(n, m);
    matB = allocMat(m, l);
    matC = allocMat(n, l);

    initMat(matA, n, m);
    initMat(matB, m, l);

    for(int i = 0; i < n; ++i){
        pthread_create(&threads[i], NULL, multRow, (void *)(size_t) i);
    }

    for(int i = 0; i < n; ++i){
        pthread_join(threads[i], NULL);
    }

    printf("Matrix A: \n");
    printMat(matA, n, m);
    printf("Matrix B: \n");
    printMat(matB, m, l);
    printf("Matrix C: \n");
    printMat(matC, n, l);

    freeMat(matA, n);
    freeMat(matB, m);
    freeMat(matC, n);
    return 0;
}
