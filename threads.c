#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

struct timeval t0,tf;
double prom=0.0;

void  *product(void *arg){
	sleep(0);
}

void *client(void *arg){
	pthread_t h;
	double promClient = 0.0;
	pthread_mutex_t *mutex = arg;
	pthread_mutex_lock(mutex);
	for(int products = 1; products <= 50; products++){
		gettimeofday(&t0, NULL);
		pthread_create(&h, NULL, product, NULL);
		pthread_join(h, NULL);
		gettimeofday(&tf, NULL);
		unsigned int tf_usec = tf.tv_usec;
		unsigned int t0_usec = t0.tv_usec;
		promClient = tf_usec - t0_usec;
	}
	printf("El tiempo de atención al cliente es: %.0f ms\n", promClient);
	pthread_mutex_unlock(mutex);
}

void main(){
	pthread_t hc;
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);
	double promCashier = 0.0;
	for(int cashiers = 1; cashiers <= 10; cashiers++){
		gettimeofday(&t0, NULL);
		for(int clients = 1; clients <= 100; clients++){
			pthread_create(&hc, NULL, client, &mutex);
			pthread_join(hc, NULL);
		}
		gettimeofday(&tf, NULL);
		unsigned int tf_usec = tf.tv_usec;
		unsigned int t0_usec = t0.tv_usec;
                promCashier = tf_usec - t0_usec;
		prom += promCashier;
		printf("\tTiempo de atención de la cajera %d: %.0f ms\n\n", cashiers, promCashier);
	}
	pthread_mutex_destroy(&mutex);
	printf("El tiempo total de atención es: %.0f ms\n", prom);
}
