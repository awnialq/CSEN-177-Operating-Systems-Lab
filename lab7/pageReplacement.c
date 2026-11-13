// Name: Awni AlQuraini
// Date: 11/11/2026
// Title: Lab 7
// Description: Implements the FIFO, LRU, and 2nd chance page replacement algorithms
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
    int last_used;
    bool was_ref;
} ref_page;

typedef enum{FIFO, LRU, SECOND, OOPS} algo_type;

algo_type get_algorithm(char* s){
    if (strcasecmp(s, "FIFO") == 0 || strcmp(s, "0") == 0) return FIFO;
    if (strcasecmp(s, "LRU")  == 0 || strcmp(s, "1") == 0) return LRU;
    if (strcasecmp(s, "SC")   == 0 || strcasecmp(s, "SECOND") == 0 || strcmp(s, "2") == 0) return SECOND;
    return OOPS;
}

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Usage: %s <cache size> <algorithm: FIFO, LRU, or SECOND>\n", argv[0]);
        return 0;
    }
    algo_type algorithm = get_algorithm(argv[2]);
    if(algorithm == OOPS){
        printf("Invalid algorithm. Use one of the following: FIFO, LRU, SECOND\n");
        return 0;
    }
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int placeInArray = 0;
    int time = 0;
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
         cache[i].last_used = time;
         cache[i].was_ref = false;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        bool foundInCache = false;
        ++time;
        for(i = 0; i < C_SIZE; ++i){
            if(cache[i].pageno == page_num){
                foundInCache = true;
                break;
            }
        }

        // Handle hits depending on the algo
        if(foundInCache){
            switch(algorithm){
                case FIFO: break;
                case LRU:
                    cache[i].last_used = time;
                    break;
                case SECOND:
                    cache[i].was_ref = true;
                    break;
                default: break;
            }
            continue;
        }
        ++totalFaults;

        // Handle misses depending on the algo
        switch(algorithm){
            case FIFO:
                printf("%d\n", page_num);
                cache[placeInArray].pageno = page_num;
                placeInArray = (placeInArray + 1) % C_SIZE;
                break;
            case LRU:
                int last_used_idx = 0;
                for(i = 0; i < C_SIZE; ++i){
                    if(cache[last_used_idx].last_used > cache[i].last_used){
                        last_used_idx = i;
                    }
                }
                printf("%d\n", page_num);
                cache[last_used_idx].pageno = page_num;
                cache[last_used_idx].last_used = time;
                break;
            case SECOND:
                while(cache[placeInArray].was_ref){
                    cache[placeInArray].was_ref = false;
                    placeInArray = (placeInArray + 1) % C_SIZE;
                }                
                printf("%d\n", page_num);
                cache[placeInArray].pageno = page_num;
                cache[placeInArray].was_ref = false;
                placeInArray = (placeInArray + 1) % C_SIZE;
                break;
            default: break;
        }
    }
    return 0;
}
