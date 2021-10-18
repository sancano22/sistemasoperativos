#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>


#define TAMANO 256
unsigned t0,t1;


int configuracion[2];

void LeerConfiguracion(void * data){
  char *NombreArchivo=(char *) data;
  FILE *fp = fopen(NombreArchivo, "r");
  int lineas=0;

  if((fp!=NULL)){
    char buffer[TAMANO];
    while(fgets(buffer,sizeof(buffer),fp)){
        configuracion[lineas]= atoi(buffer);
        //printf("%s",buffer);
        lineas++;
    }
  }
  

  fclose(fp);

}

void saludos(){
	t1=clock();
    double tiempo=(double) (t1-t0)/CLOCKS_PER_SEC;
    if(tiempo<configuracion[0]){
    	printf("Hola Mundo");
    }else{
         exit (0);
    }

}



int main(int argc, char * argv){
   t0=clock();
   LeerConfiguracion("config.txt");
   pthread_t th[configuracion[0]];

   for (int i=0;i<configuracion[0];i++){
        pthread_create(&th[i],NULL,(void*)saludos,NULL);
    }

   for (int i=0;i<configuracion[0];i++){
        pthread_join(th[i],NULL);
   }
    
   
   


}