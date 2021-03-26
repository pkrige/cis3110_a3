#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h>

typedef struct process{
    char p_id;
    int req_mem;
    time_t time_added;
    int swapped;
} process;

typedef struct my_queue{
    int start, end, size;

    process* processes;
} my_queue;

typedef struct memory{
    process mem[128];

    int next_element;

    int size;
    int capacity;

    //stats variables
    double usage;
    double average_util;
} memory;

process* readfile(char* filename);
my_queue* makeQueue(process* to_add);
process dequeue(my_queue* queue);
void enqueue(my_queue *queue, process to_add);
void free_structs(my_queue* queue);
void mem_store(memory* my_mem, process to_store);
void mem_swap(memory* my_mem,process to_swap);
