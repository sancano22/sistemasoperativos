#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <curl/curl.h>

#define TAMANO 256

int configuracion[2];
char * paginas[TAMANO];
char * paginasVisitadas[TAMANO];


void spider (void *data){
	 
     char *dato=(char *) data;
     printf("%s",dato);

}



//solo lee el contenido html
void LeerContenido (char * data) {
    CURL *curl;
    char *fp;
    CURLcode res;

    char *dato = (char * ) data;
   
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, dato);
 
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s: %s\n",   curl_easy_strerror(res),dato);

        curl_easy_cleanup(curl);

        //printf("\n%s", fp); 
   }
   
}

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
    FILE *fp = fopen("visitados.txt", "r");
    char linea[TAMANO];
    int i=0; //conteo lineas
    while ((fgets(linea,TAMANO,fp))!=NULL){
         printf("%d",strcmp(limpiar(linea),limpiar(sitio)));
            if(strcmp(limpiar(linea),limpiar(sitio)) == 0) {
                 printf("Sitio visitado %s",sitio);
                 return 1;
            }
               
    
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
       while ((fgets(linea,TAMANO,fp))!=NULL){
            //printf("Linea %s",linea);
            //seccion critica
        
            paginas[i]=linea; //guardo en un arreglo las páginas
            //debo sacarla de la lista: aquí falta
            if(!Visitado(paginas[i])){//verificar que no ha sido visitada, debo leer en archivo visitado
                printf("No ha sido visitada %s",paginas[i]); //agregar  lista de visitados
                //agregar en lista paginasVisitadas[]
                EscribirArchivo(linea); //agregar en visitados.txt
                LeerContenido(linea);  //leer el codigo html
                //debe volver a paso 1


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
    
    for (int i=0;i<configuracion[0];i++){
        pthread_create(&th[i],NULL,(void*)LeerArchivo,(char*) "sitios.txt");
    }

    for (int i=0;i<configuracion[0];i++){
        //pthread_join(th[i],NULL);
    }

    
	LeerArchivo("sitios.txt");


	
	return 0;
}