#!/bin/bash

Proceso(){

   ps -ef | awk '{print $1 " " $2 " " $3 " " $8}' > procesos.txt

   FILE="procesos.txt"

   while IFS= read linea
   do
   	 uid="$(echo $linea | awk '{print $1}')"
       pid="$(echo $linea | awk '{print $2}')"
       

       echo $uid " " $pid >>TablaNueva.txt
       

   done < "$FILE"
   rm $FILE



   echo "proceso ejecutado"

}

Memoria(){

	cat /proc/meminfo | grep "MemTotal" > memoria.txt

	cat /proc/meminfo | grep "MemFree" >> memoria.txt

	echo "proceso memoria"

}


while getopts ':p,:m' option;
do
	case "${option}" in
	   p) Proceso ;;
	   m) Memoria ;;

	   *) echo "opción invalida" ;;
	esac
done





#echo "proceso ejecutando"
#Proceso


