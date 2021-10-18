#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>


#define sillas 5
#define izquierda (numFilosofos+4)%sillas
#define derecha (numFilosofos+1)%sillas

typedef enum{
	pensando, comiendo, hambriento, terminado
}status;

status estado[sillas];
sem_t mutex;
sem_t S[sillas];

int filosofos[sillas]={1,2,3,4,5};

void comprobar (int numFilosofos){
   if(estado[numFilosofos]==hambriento && estado[izquierda]!=comiendo && estado[derecha]!=comiendo){
       estado[numFilosofos]=comiendo;
          //usleep(random()%2000000);
       printf("filosofo %d coge tenedor %d y %d",numFilosofos+1,izquierda,numFilosofos+1);
       printf("filosofo %d come y termina\n",numFilosofos+1);
       estado[numFilosofos]=terminado;
   }
}


void tomarPalillo(int numFilosofos){
   sem_wait(&mutex); //bloquea semaforo
   estado[numFilosofos]=hambriento;
   printf("filosofo %d esta  hambriento\n",numFilosofos+1);
   comprobar(numFilosofos);
   sem_post(&mutex); //desbloquea seccion critica
   sem_wait(&S[numFilosofos]); //bloquea al filosofo
}

void soltarPalillo(int numFilosofos){
   sem_wait(&mutex); //cerramos semáforo

   estado[numFilosofos]=pensando;
   comprobar(izquierda);
   comprobar(derecha);
   sem_post(&mutex); //abrir semáforo
}

void *filosofo(void *num){

   while(estado [* (int *) num]!=terminado){
        int *i;
        i=(int *) malloc (sizeof(int));
        i=num;

        //usleep(random()%2000000);
        tomarPalillo(*i);

        if(estado[*i]==terminado) printf("el filosofo %d se ha ido",*i+1);
        else soltarPalillo(*i);

        if(estado[*i]==terminado){
          printf("el filosofo %d se ha ido\n",*i+1);
          sem_post(&S[*i]);
          pthread_exit(NULL);
        }else{
           //usleep(random()%2000000);
           soltarPalillo(*i);
        }
   }
	
}





int main(){
   int i;
   int salida=0;

   pthread_t hilos[sillas];
   sem_init(&mutex,0,1);

   for(i=0;i<sillas;i++){
      sem_init(&S[i],0,0);
   }

   for(int i=1;i<sillas;i++){
        pthread_create(&hilos[i],NULL, (void *)filosofo,(void *) &filosofos[i]);
   }



   for(int i=1;i<sillas;i++){
        pthread_join(hilos[i],NULL);
        salida++;
   }



}