#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *textfile;

    if ( argc <= 2 ) {
        printf("Uso: %s <nombre del archivo> <tamaño de buffer de lectura>\n",
            argv[0]);
        exit(1);
    }

    int MAX_LINE_LENGTH = atoi(argv[2]);
    char *my_file = argv[1];
    textfile = fopen(my_file, "r");
    char *line = (char *) malloc(sizeof(char) * MAX_LINE_LENGTH);

    if(textfile == NULL) {
        printf("No pude abrir el archivo %s\n", my_file);
        exit(1);
    }

    while(fgets(line, MAX_LINE_LENGTH, textfile))
        printf("%s", line);

    fclose(textfile);

    free(line);
    exit(0);
}
