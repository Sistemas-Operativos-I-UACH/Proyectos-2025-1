//Archivos de Cabecera 
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

// Verifica si una cadenaNumeros contiene solo números (PID válido)
// Ya que el directorio de procesos solo lleva nombres numericos
int NomNUMERICO(const char *cadenaNumeros) {
    while (*cadenaNumeros) {
        if (!isdigit(*cadenaNumeros++)) {
            return 0;
        }
    }
    return 1;
}
// Imprime en pantalla el contenido del archivo con el buffer establecido por el usuario
void imprimirARCHIVO(const char *NombreArchivo, int tamanioBuffer) {

    //Abre el archivo que se le indico.
    FILE *archivo = fopen(NombreArchivo, "r");
    if (!archivo) {
        return;
    }
    char buffer[1024];
    int lecturaBuffer = (tamanioBuffer > 1024) ? 1024 : tamanioBuffer;

    while (fread(buffer, 1, lecturaBuffer, archivo)){
        fwrite(buffer, 1, lecturaBuffer, stdout);
    }
    // fwrite y stdout se encargan de escribir el contenido en pantalla.
    fclose(archivo);
}
// Crea la lista de los procesos y verifica sin son del Kernel o del Usuario
void listarPROCESOS() {
    DIR *dir = opendir("/proc");
    if (!dir) return;

    struct dirent *entrada;
    //Aqui recorre los directorios hasta que no encuentre mas
    while ((entrada = readdir(dir)) != NULL) {
        //Con la funcion de ayuda, determina si es de proceso, ya que empieza con puros numeros
        if (NomNUMERICO(entrada->d_name)) {
            char ruta[512];
            //Crea una ruta de archivo completa de Id de proceso
            snprintf(ruta, sizeof(ruta), "/proc/%s/status", entrada->d_name);
            FILE *archivo = fopen(ruta, "r");

            //Aquí empieza a recorrer los procesos para guardar su información
            if (archivo){
                char linea[256];
                char nombre[256] = "(desconocido)";
                //se inicializa en -1 para indicar que no se ha encontardo nada
                int uid = -1;
                //lee linea por linea el contenido del archivo
                while (fgets(linea, sizeof(linea), archivo)) {
                    //Si la linea empieza con "Name" enotnces nos dice que contiene el
                    //nombre del proceso
                    if (strncmp(linea, "Name:", 5) == 0) {
                        //Se extrae el nombre y se guarda en la variable nombre
                        sscanf(linea, "Name:\t%255s", nombre);
                    }
                    //Si la linea empieza con "UID" enotnces nos dice que contiene el
                    //UID del proceso
                    if (strncmp(linea, "Uid:", 4) == 0) {
                        //Se extrae el UID y se guarda en la variable uid
                        sscanf(linea, "Uid:\t%d", &uid);
                        break;
                    }
                }
                fclose(archivo);
                //Imprime en pantalla los processos con su PID, su nombre, y si lo usa el Kernel o el Usuario
                printf("PID: %s\n \tNombre: %s\n\t\tTipo: %s\n\n",
                    entrada->d_name,
                    nombre,
                    (uid == 0) ? "Kernel" : "Usuario");
            }
        }
    }
    //Cierra el directorio
    closedir(dir);
}


//Esta es la funcion principal del programa
int main(int argc, char *argv[]) {
    if (argc != 3) {
        // Aquí termina el programa con error
        return 1;
    }
    int tamanioBuffer = atoi(argv[2]);
    imprimirARCHIVO(argv[1], tamanioBuffer);
    listarPROCESOS();

    //Aquí termino el programa sin error
    return 0;
}
