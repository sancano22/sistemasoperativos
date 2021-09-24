#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


struct parametros{
	int id;
	char *nombre;
	char *apellidos;
};



void *datos(void *arg){
	
    struct parametros *p;

    p=(struct parametros *) arg;

    printf("dato id=%d\n",p->id);
    printf("dato nombre=%s\n",p->nombre);


}


int main (int argc, char *argv[]){

	pthread_t h1;
	pthread_t h2;

	struct parametros p1;
	struct parametros p2;

	p1.id = 1;
	p1.nombre ="juanito";
	p1.apellidos ="perez";

	p2.id = 2;
	p2.nombre = "juanita";
	p2.apellidos = "perez";


    pthread_create(&h1,NULL, datos, (void *)&p1);
	pthread_create(&h2,NULL, datos, (void *)&p2);


	pthread_join(h1,NULL);
	pthread_join(h2,NULL);


	printf("Fin\n");
    

}