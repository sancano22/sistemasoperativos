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

Memoria(){
    
    mem=$(cat /proc/meminfo | grep 'MemTotal' | awk '{print $2}')
    
    men1=$(echo "scale=1;$mem/1024/1024" | bc -l )

    echo -e "Total  \t\t\tTotal2\n$men1\t\t\t$men1"

}




option1="${1}"
option2="${2}"


case "$option1" in 
    ps)
       
      Procesos $false;;

    -m) 
       #echo "script m ${2}"
       Memoria;;

     -help)
       echo "ayuda";;

esac 	


