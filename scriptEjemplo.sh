#!/bin/bash

# comentario 1
# comentario 2

#pasar parametros
num1=$1
num2=$2

#condicionales 
if [[ $num1 -gt $num2 ]];
then echo "el numero $num1 es mayor que $num2"
else 
	echo "el numero $num2 es mayor que $num1"
fi

#bucle
for numero in 1 2 3 ;
do
	echo este es un numero: $numero
done
