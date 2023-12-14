#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int pipe_fd[2];

    // Crear la tubería
    if (pipe(pipe_fd) == -1) {
        perror("Error al crear la tubería");
        return EXIT_FAILURE;
    }

    // Crear un proceso hijo
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error al hacer fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        // Proceso hijo: Configurar la salida estándar para escribir en la tubería
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);

        // Redirigir la entrada desde archivo1.txt
        int inputFile = open("archivo1.txt", O_RDONLY);
        if (inputFile == -1) {
            perror("Error al abrir archivo1.txt");
            exit(EXIT_FAILURE);
        }
        dup2(inputFile, STDIN_FILENO);
        close(inputFile);

        // Ejecutar el comando "grep a1"
        char *grep_args[] = {"grep", "a1", NULL};
        execve("/usr/bin/grep", grep_args, NULL);

        perror("Error en execvp");
        exit(EXIT_FAILURE);
    } else {
        // Proceso padre: Configurar la entrada estándar para leer desde la tubería
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);

        // Crear un nuevo archivo2.txt y redirigir la salida estándar hacia él
        FILE *outputFile = fopen("archivo2.txt", "w");

        if (!outputFile) {
            perror("Error al abrir el archivo de salida");
            return EXIT_FAILURE;
        }

        dup2(fileno(outputFile), STDOUT_FILENO);

        // Ejecutar el comando "wc"
        char *wc_args[] = {"wc", NULL};
        execve("/usr/bin/wc", wc_args, NULL);

        perror("Error en execvp");
        fclose(outputFile);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
