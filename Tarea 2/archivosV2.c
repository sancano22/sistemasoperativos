#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define TAMANO 256
char visitasUrl[30][300];

#include "spider.h"



int configuracion[2],visitas=0;
char * paginas[TAMANO];
char * paginasVisitadas[TAMANO];





void EscribirArchivo(void *data){
     char *url=(char *) data;
     char *buffer;
     FILE *fp = fopen("visitados.txt", "a+");
     if(fp==NULL){
        printf("Error abriendo archivo");
        exit(1);
     } 
     else{
        
        fprintf(fp, "%s\n",url);
     
       
      }

     fclose(fp);


}

void SacarURL(char *archivo, char *data, int lineaTexto){
     char *NombreArchivo=(char *) archivo;
     char *url=(char *) data;


        FILE *fp1 = fopen(NombreArchivo, "r+");
        FILE *fp2 = fopen("sitiosCopia.txt", "a+");

        if (fp1 == NULL){
             printf("Error al leer el archivo\n");
             
        }else{
            char linea[TAMANO];
            int i=0; //conteo lineas
               while ((fgets(linea,TAMANO,fp1))){
                    
                    if(i!=lineaTexto){
                        fprintf(fp2, "%s",linea);
                        printf("entro %s, %s",linea,url); 

                    }     
                    i++;         
            
               }

               
        }

        fclose(fp1);
        fclose(fp2);
        remove(NombreArchivo);
        rename("sitiosCopia.txt",NombreArchivo);

}

char *limpiar(char *str){
    int i=0,j=0;
    while(str[i]){
        if(str[i] != ' ')
            str[j++]=str[i];
        i++;
    }
    str[j]='\0';
    return str;
}


int Visitado(void *url){

    char *sitio=(char *)url;

    
    
    for(int i=0;i<visitas;i++){
        if(paginasVisitadas[i]==sitio)
            return 1;
        else return 0;
     }


    return 0;
}

void LeerArchivo(void *data){
  char *NombreArchivo=(char *) data;
  FILE *fp = fopen(NombreArchivo, "r");

    if (fp == NULL){
         printf("Error al leer el archivo\n");
         
    }else{
       char linea[TAMANO];
       int i=0; //conteo lineas
       while ((fscanf(fp,"%[^\n]",linea))!=EOF){
            //printf("Linea %s",linea);
            //seccion critica
        
            paginas[i]=linea; //guardo en un arreglo las páginas
            //debo sacarla de la lista: aquí falta
            if(!Visitado(paginas[i])){//verificar que no ha sido visitada, debo leer en archivo visitado
                //printf("No ha sido visitada %s",paginas[i]); //agregar  lista de visitados
                paginasVisitadas[visitas]=paginas[i]; //agregar en lista paginasVisitadas[]
                spider(paginasVisitadas[visitas]);

                int longitud=sizeof(visitasUrl)/sizeof(visitasUrl[0]);
                
                for(int k=0;k<longitud;k++){

                   if(strlen(visitasUrl[k])>0){
                       printf("visitado %s\n\n",visitasUrl[k]);
                        //EscribirArchivo(); //agregar en visitados.txt
                    }
                 }

                
                visitas++;
               


            }
            
            

            //seccion critica
            i++;        
    
       }

    }

      fclose(fp);

}

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


int main(int argc, char * argv){
  
    LeerConfiguracion("config.txt");

    pthread_t th[configuracion[0]];
    
    /* creamos los hilos 
    for (int i=0;i<configuracion[0];i++){
        pthread_create(&th[i],NULL,(void*)LeerArchivo,(char*) "sitios.txt");
    }

    for (int i=0;i<configuracion[0];i++){
        pthread_join(th[i],NULL);
    }
    */

	LeerArchivo("sitios.txt");
    //spider("http://www.google.com/");
    
	return 0;
    }
