#include <stdio.h> 
//librería que contiene funciones de cabeceras E/S
#include <unistd.h> 
//librería que contiene funciones para el manejo directorios y archivos
#include <sys/types.h> 
//librería que contiene funciones de búsqueda y ordenamiento de directorios y manipulación de archivos.
int main (void){
	pid_t idHijo;
	pid_t idPropio;
	idPropio=getpid(); //se obtiene el id proceso actual
	idHijo=fork(); //crea un proceso hijo
	if (idHijo==-1){
	   	printf("error al realizar la bifurcación");
  		return 1; //interrumpe la ejecución	   
	}
	if(idHijo==0)
	  	printf("soy el hijo con id %ld id proceso original %ld\n",(long)getpid(), (long)idPropio);
	else 
		printf("Soy el padre con id %ld id proceso original %ld\n", (long) getpid(),(long)idPropio);	
        return 0;
}
