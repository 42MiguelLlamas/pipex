#include <stdio.h>
int main(int argc, char *argv[], char *envp[]) {
    // Imprimir todas las variables de entorno
    for (int i = 0; envp[i] != NULL; i++) {
        printf("Variable: %s\n", envp[i]);
    }

    return 0;
}