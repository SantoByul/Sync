CC = gcc
CFLAGS = -Wall -pthread

all: sync_car

sync_car: sync_car.c sync_car-runner.c sync_car.h
	$(CC) $(CFLAGS) -o sync_car sync_car.c sync_car-runner.c

tsan: sync_car.c sync_car-runner.c sync_car.h
	$(CC) $(CFLAGS) -fsanitize=thread -g -o sync_car_tsan sync_car.c sync_car-runner.c

clean:
	rm -f sync_car sync_car_tsan

.PHONY: all tsan clean