#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/time.h>

struct timeval tinicio, tfin;
double promedio = 0.0;

void *transactions(void **arg){
	
}

void create_process(void *arg){
	int i;
	pid_t rf;
	rf = fork();
	switch(rf){
		case -1:
			perror("Error al crear el proceso\n");
			break;
		case 0:
			for(i=0; i<=50; i++){
				printf("Soy el hijo\n");
			}
			break;
		default:
			for(i=0; i<=50; i++){
				printf("Soy el padre\n");
			}
			wait(0);
			printf("Mi proceso hijo ha terminado\n");
	}
	printf("Final de ejecución de %d \n", getpid());
}

void create_thread(void *arg){
	pthread_t h;
	double *num;
	num = (double*) arg;
	double **number = &num;
	pthread_create(&h, NULL, transactions, (void**) number);
	pthread_join(h, NULL);
}

void main(){
	create_thread(&);
}
