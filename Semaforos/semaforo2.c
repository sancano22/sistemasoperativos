#include <stdio.h>
#include <pthread.h>

#define SALDO 1000
int saldo_inicial=SALDO;


void *compras(void * arg){
     char * texto;
     texto=(char *) arg;

     int productos=10;
     int monto=100;
     for(int i=0;i<productos;i++){
        if(saldo_inicial>0){
         saldo_inicial=saldo_inicial-monto;
        }else{
            printf("No queda suficientes fondos en su saldo (%s),%d \n",texto, saldo_inicial);
        }
     }
}


int main(){
    pthread_t a,p;
    
    pthread_create(&a,NULL, compras,(void *) "ana");
    pthread_create(&p,NULL, compras, (void *) "pepe");

    pthread_join(a,NULL);
    pthread_join(p,NULL);



    return 0;
}