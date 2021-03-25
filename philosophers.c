#include "a3_1.h"

pthread_t *philo_id;
pthread_mutex_t *chopstick;
int num_phil;
int eat_times;

int main(int argc, char** argv){    
    void *return_val;
    if(argc < 3){
        perror("Please enter the number of philosophers and the length of time it takes to eat.\n");
    }
    else {

        num_phil = atoi(argv[1]);
        eat_times = atoi(argv[2]);

        philo_id = malloc(num_phil*sizeof(pthread_t));
        chopstick = malloc(num_phil*sizeof(pthread_mutex_t));

        for(int i = 0; i < num_phil; i++){
            pthread_mutex_init(&(chopstick[i]),NULL);
        }
        for(int i = 0; i < num_phil; i++){
            pthread_create(&philo_id[i],NULL, (void *) dining, (int *) i);
        }
        for(int i = 0; i < num_phil; i++){
            pthread_join(philo_id[i],&return_val);
        }
        for(int i = 0; i < num_phil; i++){
            pthread_mutex_destroy(&chopstick[i]);
        }

        free(philo_id);
        free(chopstick);
    }
    return 0;
}

void* dining(int pos){
    int run = 0;
    while(run < eat_times){
        printf("Philosopher %d is thinking\n",pos + 1);
        pthread_mutex_trylock(&chopstick[pos]);
        pthread_mutex_trylock(&chopstick[(pos+1)%num_phil]);

        printf("Philosopher %d is eating\n",pos+1);
        sleep(rand()%num_phil);

        pthread_mutex_unlock(&chopstick[pos]);
        pthread_mutex_unlock(&chopstick[(pos+1)%num_phil]);

        run++;
    }
    return NULL;
}
