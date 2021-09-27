#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define TAM 20
#define NUM_ITEMS 100
//variables globales
int buffer[TAM];
int n=0;

sem_t mutex, Sproduce,Sconsume; 




int producir_dato(){
	static int contador=1;
	return contador++;
}

void consumir_dato(int dato){
	sem_wait(&mutex);
	printf("Dato recibido%d\n", dato);
	sem_post(&mutex);
}


void* productor(void* arg){
     for(int i=0;i<NUM_ITEMS;i++){

        sem_wait(&Sproduce);
        int dato=producir_dato();

        sem_wait(&mutex); //seccion critica
        buffer[n]=dato;
        n++;
        sem_post(&mutex);
        sem_post(&Sconsume);

     }
     return NULL;
}


void* consumidor(void* arg){

	for(int i=0;i<NUM_ITEMS;i++){
		sem_wait(&Sconsume);
		sem_wait(&mutex);
		int dato=buffer[n-1];
		n--;
		sem_post(&mutex);

		//consumo el valor sacado
		consumir_dato(dato);

		sem_post(&Sproduce);

	}

}

int main (int argc, char *argv[]){

    pthread_t producir, consumir;

    //inicializamos semaforos

    sem_init(&mutex,0,1);
    sem_init(&Sproduce,0, TAM);
    sem_init(&Sconsume,0, 0);

    pthread_create(&producir,NULL,productor,NULL);
    pthread_create(&consumir,NULL,consumidor,NULL);


    pthread_join(producir, NULL);
    pthread_join(consumir, NULL);


    sem_destroy(&mutex);
    sem_destroy(&Sproduce);
    sem_destroy(&Sconsume);


    


}