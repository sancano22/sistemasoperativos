#include <curl/curl.h>




void spider(char *data);


// Estructura auxiliar para guardar la cadena de texto con el html
//  y el tamaño que esta tiene
typedef struct mem
{
    char *memory;
    size_t size;
} mem;


// Función que es llamada por curl cada vez que recibe un bloque de datos desde la url
size_t write_callback(void *contenido, size_t size, size_t nmemb, void *userp)
{
    // Calculamos el tamaño del bloque
    size_t tamanioreal = size * nmemb;
    // Recuperamos el puntero a la memoria donde dijimos que íbamos a dejar todo
    mem *memoria = (mem *)userp;

    // Intentamos extender el tamaño de la memoria al tamaño actual + tamaño del bloque nuevo que entra
    char *ptr = realloc(memoria->memory, memoria->size + tamanioreal + 1);

    // Si retorna null, entonces no hay memoria y esto falló
    if (!ptr)
    {
        printf("Sin Memoria!");
        return 0;
    }

    // Si hay memoria, re ajustamos los punteros y copiamos el contenido del nuevo
    //   bloque al final del bloque anterior
    memoria->memory = ptr;
    memcpy(&(memoria->memory[memoria->size]), contenido, tamanioreal);
    memoria->size += tamanioreal;
    memoria->memory[memoria->size] = 0;

    // Retornamos el tamaño del bloque recibido
    return tamanioreal;
}

// Función que utiliza curl.h para extraer el html de una página y guardarlo en memoria
mem *fetch_url(char *url, CURL* curl)
{
    // Inicializaciones básicas
    CURLcode res;
    mem *memoria = (mem *)malloc(sizeof(mem));
    // Esto se irá ajustando de acuerdo a cuánto necesite
    memoria->memory = malloc(1);
    memoria->size = 0;


    if (!curl)
    {
        printf("No se pudo inicializar :c \n");
        return memoria;
    }

    // Se inicializa la petición de curl con la url a pedir
    curl_easy_setopt(curl, CURLOPT_URL, url);

    curl_easy_setopt( curl, CURLOPT_NOSIGNAL, 0 );

    // Se establece que cada vez que se recibe un bloque de datos desde la url,
    //  se llama a la función write_callback
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    // El contenido lo escribiermos sobre la variable memoria
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)memoria);

    // Algunas páginas exigen que se identifiquen, decimos que estamos usando curl
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    // Ejecutamos la petición
    res = curl_easy_perform(curl);

    // Si la petición falla, imprimimos el error.
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() falla: %s\n", curl_easy_strerror(res));
    }

    // Retornamos el contenido html
    return memoria;
}

// Araña de un webcrawler.
//  Esta sólo extrae los enlaces y los imprime.
void spider(char *data){

     int leidos=0;
     // Inicializamos la librería curl y una instancia para manejar las solicitudes
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();


    char *url = (char *)data;
    // Extrae todo el html de la url
    mem *memoria = fetch_url(url, curl);
    // Comienza buscando el primer enlace (Asumiendo que está en una propiedad href)
    char *inicio = strstr(memoria->memory, "href=\"");
    char *final = NULL;
    int size;
    char *aux;

     //printf("a curl %s",url);

    // Se va recorriendo cada propiedad href de la página
    //  y se le imprime
    do
    {
        // para quitar  ' href=" ' del string
        inicio += 6;
        // Se busca desde el inicio hasta el siguiente ", -1 para que no lo contenga
        final = strstr(inicio, "\"") - 1;

        // +2 por el \0 y el espacio extra.
        size = final - inicio + 2;
        aux = (char *)malloc(size);
        strncpy(aux, inicio, size + 1);

        // Se coloca el caracter nulo
        aux[size - 1] = 0;

        // Cuando se enlaza dentro del mismo dominio, es costumbre no colocar la url completa
        // para asegurarnos que no se recorra el mismo enlace más de una vez, debe comenzar con su dominio
        if (aux[0] == '/')
        {
            //return "";
            //printf("segundos %s%s\n\n", url, aux);
            strcpy(visitasUrl[leidos],strcat(url,aux));
            //printf("spider %s leido :%d\n", visitasUrl[leidos],leidos);
            
           
        }
        else
        {
            //return "";
            //printf("primeros %s\n\n", aux);

            strcpy(visitasUrl[leidos],aux);
            //printf("spider %s leido :%d\n", visitasUrl[leidos],leidos);
            
        }
        // Se libera la memoria porque un webcrawler puede requerir demasiados recursos
        free(aux);
        leidos++;
        // Busca el siguiente enlace
    } while ((inicio = strstr(inicio, "href=\"")) != NULL);

   
}

