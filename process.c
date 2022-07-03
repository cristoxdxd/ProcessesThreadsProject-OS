#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <sys/wait.h>

#define MAX 10
struct timeval begin, end;
int i=1;
int main(){
	int pid;
	gettimeofday(&begin, 0);
	double lapso;
	double lapso1,lapso2;
	for (int cashiers = i; cashiers <= MAX; cashiers++){
		pid = fork();
		gettimeofday(&begin, 0);
		switch(pid){
			case -1:
				perror("Error al crear proceso\n");
				break;
			case 0:
				for(int clients = 1; clients <= 100; clients++){
					unsigned long microseconds1=0;
					for(int products = 1; products <=50; products++){
						gettimeofday(&begin,0);
						sleep(0);
						gettimeofday(&end, 0);
						microseconds1 = end.tv_usec - begin.tv_usec;
					}
					lapso2 =microseconds1;
					printf("El tiempo de atencion al cliente es: %.0f\n ",lapso2);
				}
				
				break;
			default:
				wait(0);
			        sleep(0);
				exit(0);
				break;
		}
				gettimeofday(&end, 0);
				unsigned long seconds1 = end.tv_sec - begin.tv_sec;
				unsigned long microseconds1 = end.tv_usec - begin.tv_usec;
				lapso1 = microseconds1;
				lapso +=lapso1;
		printf("Tiempo de atención cajera %d: %.3f ms.\n", cashiers, lapso1);
		//printf("\n\n\t\tCajera: %d\n\n", cashiers);
	}
	/*gettimeofday(&end, 0);
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	lapso = microseconds;*/
	printf("Tiempo de ejecucion: %.3f ms.\n", lapso);
	exit(0);
}
