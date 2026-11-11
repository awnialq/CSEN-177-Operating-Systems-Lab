// Name: Awni AlQuraini
// Date: 11/11/2026
// Title: Lab 7 - Part 1
// Description: Generates a testInput.txt file for future parts
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if(argc < 3){
        printf("Usage: %s <# of numbers> <max page number>\n", argv[0]);
        return 0;
    }
    int numRequests = atoi(argv[1]);
    int maxPageNumber = atoi(argv[2]);
    FILE *fp;
    char buffer [sizeof(int)];
    int i;
    fp = fopen("testInput.txt", "w");
    srand(time(NULL));
    for (i=0; i < numRequests; i++){
        sprintf(buffer, "%d\n", rand()%maxPageNumber);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}