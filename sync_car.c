#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "sync_car.h"

void station_init(struct station *station){

    station->waiting = 0;
    pthread_mutex_init(&station->lock, NULL);

    return;
}

void station_load_car(struct station *station, int count){
    pthread_mutex_lock(&station->lock);

    if (station->waiting == 0){
        pthread_mutex_unlock(&station->lock);
        return;
    }
    pthread_mutex_unlock(&station->lock);

    return;
}

void station_wait_for_car(struct station *station){

    pthread_mutex_lock(&station->lock);
    station->waiting++;
    pthread_mutex_unlock(&station->lock);
    return;
}

void station_on_board(struct station *station){

    return;
}