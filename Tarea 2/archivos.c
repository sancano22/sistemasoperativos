

    if (fp == NULL){
         printf("Error al leer el archivo\n");
         
    }else{
       char linea[TAMANO];
       int i=0; //conteo lineas
       while ((fgets(linea,TAMANO,fp))){
            //printf("Linea %s",linea);
            //seccion critica
            SacarURL(NombreArchivo, linea);
            //LeerContenido(linea); 
            //EscribirArchivo(linea);

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
        printf("%s",buffer);
        lineas++;
    }
  }
  

  fclose(fp);

}


int main(int argc, char * argv){
  
    LeerConfiguracion("config.txt");

    pthread_t th[configuracion[0]];
    
    for (int i=0;i<configuracion[0];i++){
        //pthread_create(&th[i],NULL,(void*)LeerArchivo,(char*) "sitios.txt");
    }

    for (int i=0;i<configuracion[0];i++){
        //pthread_join(th[i],NULL);
    }


	LeerArchivo("sitios.txt");


	
	return 0;
}