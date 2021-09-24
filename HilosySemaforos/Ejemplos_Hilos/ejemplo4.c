#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUMTH 10
int suma_total=0;

void suma(){
	int i,n; 
	int suma=suma_total;
	suma=suma+100;
	n=rand()%5;
	for(i=0;i<n;i++){
		printf(".");
	}
	suma_total=suma;

	printf("Suma=%d\n",suma_total);
}

int main(){
	pthread_t th[NUMTH];
	int i;
	for (i=0;i<NUMTH;i++){
		pthread_create(&th[i],NULL,(void*)suma,NULL);
	}
	for (i=0;i<NUMTH;i++){
		pthread_join(th[i],NULL);
	}


	printf("Final Suma=%d\n",suma_total);

}