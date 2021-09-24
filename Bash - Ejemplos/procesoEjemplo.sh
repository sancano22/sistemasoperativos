#!/bin/bash

Proceso(){

   ps -ef | awk '{print $1 "\t" $2 "\t\t" $3 " " $8}' > procesos.txt

   FILE="procesos.txt"

   while IFS= read linea
   do

   	 uid="$(echo $linea | awk '{print $1}')"
     pid="$(echo $linea | awk '{print $2}')"
     ppid="$(echo $linea | awk '{print $3}')"


     ps $pid | awk '{print $3}'
     #status=


    echo $uid "\t\t\t" $pid "\t\t\t" $status "\t" $ppid >>TablaNueva.txt
       

   done < "$FILE"
   rm $FILE



   echo "proceso ejecutado"

}

Memoria(){

	cat /proc/meminfo | grep "MemTotal" > memoria.txt

	cat /proc/meminfo | grep "MemFree" >> memoria.txt

	echo "proceso memoria"

}


#while getopts ':p,:m' option;
#do
#	case ${option} in
#	   p) Proceso ;;
#	   m) Memoria ;;
#
#	   *) echo "opción invalida" ;;
#	esac
#done

opcion1="${1}"
opcion2="${2}"


case ${opcion1} in 
    ps) Proceso;;
    -m) Memoria ;;
    help) 
       if [ $opcion2 = "r" ]; then
          echo $opcion2 
       fi;
       echo "ejecutar ayuda";;

    *) echo "opción invalida, no está dentro de nuestras opciones";;

esac



#echo "proceso ejecutando"
#Proceso


