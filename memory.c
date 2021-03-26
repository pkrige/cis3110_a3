#include "a3_2.h"

my_queue *queue;

int main(int argc, char* argv[]){
    if(argc < 3){
        fprintf(stderr,"INSUFFICIENT ARGUMENTS: Please enter the filename followed by the insertion style. ex. ./holes filename.txt first/next/best/worst\n");
    } else{
        memory* mem = calloc(1, sizeof(memory));
        mem->capacity = 128;

       //printf("%p is equal to %p",(void*) mem->mem, (void*) mem->last_element);

        process* to_process = readfile(argv[1]);
        queue = makeQueue(to_process);

        process temp = dequeue(queue);
        printf("Popped of the queue: pid: %c %d\n", temp.p_id, temp.req_mem);
        mem_store(mem,temp);
        
        temp = dequeue(queue);
        printf("Popped of the queue: pid: %c %d\n", temp.p_id, temp.req_mem);
        mem_store(mem,temp);

        temp = dequeue(queue);
        printf("Popped of the queue: pid: %c %d\n", temp.p_id, temp.req_mem);
        mem_store(mem,temp);


        if(strcmp("first", argv[2])== 0){
            printf("first\n");
        } else if(strcmp("next", argv[2])== 0){
            printf("next\n");
        } else if(strcmp("best", argv[2])== 0){
            printf("best\n");
        } else if(strcmp("worst", argv[2]) == 0){
            printf("worst\n");
        } else {
            printf("Please enter either first, next, best, or worst. Exiting now... Goodbye\n");
            exit(1);
        }
        free_structs(queue);
    }
    return 0;
}

process* readfile(char* filename){
    FILE *fp = fopen(filename,"r");
    char r_char;
    int r_int;
    int i = 0;
    process *processes = calloc(150,sizeof(process));

    if(fp == NULL){
        fprintf(stderr,"Could not open file %s\n",filename);
        exit(1);
    }

    while(fscanf(fp,"%c %d\n",&r_char,&r_int) != EOF){
        processes[i].p_id = r_char;
        processes[i].req_mem = r_int;
        i++;
    }

    //processes = realloc(processes,i*sizeof(process));

/*     for(int j = 0; j < i; j++){
        printf("Process ID: %c, Required Memory: %d\n",processes[j].p_id,processes[j].req_mem);
    } */

    return processes;
}

my_queue* makeQueue(process* to_add){
    my_queue *queue = malloc(sizeof(my_queue));
   
    queue->start = 0;
    queue->end = 0;
    queue->size = sizeof(to_add)/sizeof(process);

    queue->processes = to_add;

    printf("Successfully initialized the queue.\n");
    return queue;
}

void enqueue(my_queue *queue, process to_add){
    queue->end += 1;
    queue->processes[queue->end] = to_add;
    queue->size += 1;
    printf("Process %c with mem. req. %d has been added.\n",queue->processes[queue->end].p_id, queue->processes[queue->end].req_mem);
}

process dequeue(my_queue* queue){
/*     if(queue->size == 0){
        printf("Nothing to remove, queue empty.\n");
    } */

    process temp = queue -> processes[queue->start];

    queue->start += 1;
    queue->size -=1;

    return temp;
}

void free_structs(my_queue* queue){
    free(queue->processes);
    free(queue);
}

void mem_store(memory* my_mem, process to_store){
    printf("Process to add %c %d\n", to_store.p_id, to_store.req_mem);
    if((my_mem->size + to_store.req_mem) >= my_mem->capacity){
        printf("Swap with oldest\n");
        mem_swap(my_mem,to_store);
    } else {
        to_store.time_added = time(0);

        for(int i = 0; i < to_store.req_mem; i++){
            my_mem->mem[my_mem->next_element++] = to_store;
        }

        my_mem->size += to_store.req_mem;
        //printf("\t\t%d\n\r", my_mem->size);
    }
    
/*     for(int j = 0; j < my_mem->size; j++){
        printf("%c %d\n",my_mem->mem[j].p_id, my_mem->mem[j].req_mem);
    }  */
}

void mem_swap(memory* my_mem,process to_swap){
    int loc = 0;

    for(int i = 0; i < my_mem->capacity; i++){
       //printf("Time 1: %ld Time 2: %ld\n", my_mem->mem[i].time_added, my_mem->mem[loc].time_added);
        if((my_mem->mem[i].time_added < my_mem->mem[loc].time_added) && (my_mem->size - my_mem->mem[i].req_mem >= to_swap.req_mem)){
            if(my_mem->mem[i].time_added == 0){
                continue;
            }
            loc = i;
        }
    }

    process temp = my_mem->mem[loc];
    temp.swapped++;
    
    my_mem->size -= temp.req_mem;

    for(int j = loc; j < temp.req_mem; j++){
        my_mem->mem[j].p_id = 0;
        my_mem->mem[j].req_mem = 0;
        my_mem->mem[j].time_added = 0;
        my_mem->mem[j].swapped = 0;
    }

    to_swap.time_added = time(0);

    for(int m = loc; m < loc + to_swap.req_mem; m++){
        my_mem->mem[m] = to_swap;
    }
    
/*     for(int k = 0; k < my_mem->capacity; k++){
        printf("%c %d\n",my_mem->mem[k].p_id, my_mem->mem[k].req_mem);
    } */
    
    my_mem->size += to_swap.req_mem;
    
    printf(" Location of oldest: %d\n", loc);

    enqueue(queue,temp);
}