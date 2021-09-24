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

Ordenar(){
    if [ ${#1} -ne 8 ]; then echo "missuse of function Ordenar"; exit; fi

    local byte1="${1%??????}"

    local byte2="${1%????}"
    byte2="${byte2#??}"

    local byte3="${1%??}"
    byte3="${byte3#????}"

    local byte4="${1#??????}"

    echo "$byte4$byte3:$byte2$byte1"
}

ConvertirHexDecimal(){
    local ip4_1octet="0x${1%???????????}"

    local ip4_2octet="${1%?????????}"
    ip4_2octet="0x${ip4_2octet#??}"

    local ip4_3octet="${1%???????}"
    ip4_3octet="0x${ip4_3octet#????}"

    local ip4_4octet="${1%?????}"
    ip4_4octet="0x${ip4_4octet#??????}"

    local ip4_port="0x${1##*:}"

    
    printf "%d.%d.%d.%d:%d" "$ip4_4octet" "$ip4_3octet" "$ip4_2octet" "$ip4_1octet" "$ip4_port"
}




tcpConexion(){
     
    for ipp in `cat /proc/net/tcp | awk  '/.*:.*:.*/{print $10"|"$2"|"$3;}'`
    do
           uid=${ipp%%|*}
           ip_s=${ipp#*|}
           ip_origen=${ip_s%%|*}
           ip_remote=${ip_origen#*|}


           #???deben consultar para uid a que pid corresponde

           #formato de IP 255.255.255.244:port

           ipDecimal=$(ConvertirHexDecimal $ip_origen)
           
           echo $uid " " $ipDecimal
           

           #echo $ip_remote

    
    done
}





option1="${1}"
option2="${2}"


case "$option1" in 
    ps)
       
      Procesos $false;;

    -m) 
       #echo "script m ${2}"
       Memoria;;
    tcp)
       tcpConexion;;

     -help)
       echo "ayuda";;

esac 	


