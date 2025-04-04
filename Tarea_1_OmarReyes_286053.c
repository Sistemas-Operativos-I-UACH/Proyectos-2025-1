#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <cadena>\n", argv[0]);
        return 1;
    }

    char *buffer = (char *)malloc(100 * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Error al asignar memoria\n");
        return 1;
    }

    strncpy(buffer, argv[1], 99);
    buffer[99] = '\0';

    printf("Cadena copiada: %s\n", buffer);

    free(buffer);
    return 0;
}
