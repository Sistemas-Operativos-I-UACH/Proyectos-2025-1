#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    char *mensaje = malloc(100);
    char *ptr;
    ptr=mensaje;
    if(mensaje == NULL) {
        printf("No se logro guardar memoria\n");
        return 1;
    }
    if(argc < 2) {
        printf("Debe ingresar alguna cadena\n");
        free(mensaje);
        return 1;
    }
    strncpy(mensaje, argv[1], 99);
    printf("Cadena copiada: %s\n", mensaje);
    printf("Direccion de la cadena copiada: %p\n",&mensaje);
    printf("Puntero a Mensaje: %p",ptr);
    free(mensaje);
    return 0;
}