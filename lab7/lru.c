// Name: Awni AlQuraini
// Date: 11/11/2026
// Title: Lab 7
// Description: LRU page replacement algorithm showcase
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: %s <cache size>\n", argv[0]);
        return 0;
    }
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
    	/*

		
		Page Replacement Implementation Goes Here 


    	*/
    }

    printf("%d Total Page Faults\n", totalFaults);
    return 0;



}
