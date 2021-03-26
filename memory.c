#include "a3_2.h"

int main(int argc, char* argv[]){
    if(argc < 3){
        fprintf(stderr,"INSUFFICIENT ARGUMENTS: Please enter the filename followed by the insertion style. ex. ./holes filename.txt first/next/best/worst\n");
    } else{
        process* to_process = readfile(argv[1]);
        my_queue *queue = makeQueue();

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
    }
    return 0;
}

process* readfile(char* filename){
    FILE *fp = fopen(filename,"r");
    char r_char;
    int r_int;
    int i = 0;
    process *processes = calloc(50,sizeof(process));

    if(fp == NULL){
        fprintf(stderr,"Could not open file %s\n",filename);
        exit(1);
    }

    while(fscanf(fp,"%c %d\n",&r_char,&r_int) != EOF){
        
        processes[i].p_id = r_char;
        processes[i].req_mem = r_int;
        i++;
    }

    processes = realloc(processes,i*sizeof(process));

    for(int j = 0; j < i; j++){
        printf("Process ID: %c, Required Memory: %d\n",processes[j].p_id,processes[j].req_mem);
    }

    return processes;
}

my_queue* makeQueue(){
    my_queue *queue = malloc(sizeof(my_queue));
   
    queue->front = 0;
    queue->end = 0;
    queue->size = 0;

    queue->processes = malloc(sizeof(process));

    printf("Suxxessfully initialized the queue.\n");
    return queue;
}

void enqueue(my_queue *queue, process to_add){
    queue->end += 1;
    queue->processes[queue->end] = to_add;
    queue->size += 1;
    printf("Process %c with mem. req. %d has been added.\n",queue->processes[queue->end].p_id, queue->processes[queue->end].req_mem);
}
