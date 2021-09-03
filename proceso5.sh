#!/bin/bash

Procesos(){

    cd /proc
    for pid in "/proc"/*
    do
        directory="$(echo  $pid | grep -o '[^/]*$')"
        #echo $directory
        numero='^[0-9]+$'

        if [[ $directory =~ $numero ]]; then
           ruta=`"$PWD"/$directory`
           #ls $ruta
           if [[ $1 ]]; then
                uid=$(cat $ruta/status | grep -w 'Uid' | awk {'print $2'})
           else
                cat locks #procesos bloqueados
            fi
           #echo $uid
        fi
    done
}




option1="${1}"
option2="${2}"


case "$option1" in 
    ps)
       
      Procesos $false;;

    -m) 
       echo "script m ${2}";;

     -help)
       echo "ayuda";;

esac 	


