#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

typedef struct process{
    char p_id;
    int req_mem;
} process;

typedef struct my_queue{
    int front, end, size;

    process* processes;
} my_queue;

process* readfile(char* filename);
my_queue* makeQueue();
