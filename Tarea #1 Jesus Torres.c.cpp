#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: No se proporcionó ninguna cadena como argumento.\n");
        return EXIT_FAILURE;
    }

    char *mensaje = malloc(BUFFER_SIZE);
    if (mensaje == NULL) {
        fprintf(stderr, "Error: No fue posible asignar memoria dinámica.\n");
        return EXIT_FAILURE;
    }

    strncpy(mensaje, argv[1], BUFFER_SIZE - 1);
    mensaje[BUFFER_SIZE - 1] = '\0';

    printf("Contenido de la cadena ingresada: %s\n", mensaje);
    printf("Dirección de la memoria asignada: %p\n", (void *)mensaje);

    free(mensaje);
    return EXIT_SUCCESS;
}
