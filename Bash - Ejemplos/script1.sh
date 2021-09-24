#!/bin/bash

Help(){
 echo "aqui estamos presentando ayuda"
}


#####Programa principal ########
#Help 
#echo "Hola mundo"


while getopts ":h:r" option; do
	case $option in 
		h) #ayuda
 			Help
 			exit;;
 		r) #algo
  			echo "que es eso"
  			exit;;
        \?) #invalida
			echo "error opción"
    esac
done