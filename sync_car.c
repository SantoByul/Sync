#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "sync_car.h"

void station_init(struct station *station){

    station->waiting = 0;
    station->free_seats = 0;
    pthread_mutex_init(&station->lock, NULL);
    pthread_cond_init(&station->car_arrived, NULL);

    return;
}

void station_load_car(struct station *station, int count){
    pthread_mutex_lock(&station->lock);

    if (station->waiting == 0 || count == 0){
        pthread_mutex_unlock(&station->lock);
        return;
    }

    station->free_seats = count;
    pthread_cond_broadcast(&station->car_arrived);

    pthread_mutex_unlock(&station->lock);

    return;
}

void station_wait_for_car(struct station *station){

    pthread_mutex_lock(&station->lock);

    station->waiting++;

    while (station->free_seats == 0)
        pthread_cond_wait(&station->car_arrived, &station->lock);

    station->waiting--;
    station->free_seats--;

    pthread_mutex_unlock(&station->lock);

    return;
}

void station_on_board(struct station *station){

    return;
}