#include "a3_1.h"
int main(int argc, char** argv){
    pthread_t *philo_id;
    pthread_mutex_t *chopstick;
    
    if(argc < 3){
        perror("Please enter the number of philosophers and the length of time it takes to eat.\n");
    }
    else {
        int num_phil = atoi(argv[1]);
        int wait_time = atoi(argv[2]);

        philo_id = malloc(num_phil*sizeof(pthread_t));
        chopstick = malloc(num_phil*sizeof(pthread_mutex_t));

        for(int i = 0; i < num_phil; i++){
            pthread_mutex_init(&(chopstick[i]),NULL);
        }
    }
    return 0;
}