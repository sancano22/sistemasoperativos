# Curso Sistemas Operativos
Escuela de Ingeniería Informática - PUCV
# Directrices para la tarea 2 SOs
Algunas funciones se han implementado y que pueden servir de apoyo:
- Función Limpiar: limpia espacios en blanco
- Función Visitado: se encarga de leer el archivo visitados.txt y comparar contra una lista de sitios web a visitar,  si ya se ha visitado retorna un 1.
- Función EscribirArchivo: escribe un dato en el archivo visitados.txt.
- Función LeerArchivo: lee el archivo sitios.txt línea por línea.
- Función LeerConfiguración: Lee el archivo de configuración y guarda los valores en un vector llamado configuración.


# Compilación
Para compilar el código usando un SO ubuntu es: 
gcc NOMBREARCHIVO.c -lcurl -o NOMBREARCHIVO 

Si desea usar la librería phtread se debe compilar de la siguiente manera: 
gcc NOMBREARCHIVO.C -lcurl -o  NOMBREARCHIVO -lpthread



