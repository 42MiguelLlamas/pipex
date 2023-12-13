#include "pipex.h"

void ft_error_exit(void)
{
    perror("Error");
    exit(EXIT_FAILURE);
}

void ft_check(char **argv)
{
    if (access(argv[1], R_OK == -1))
        ft_error_exit();
    if (access(argv[4], W_OK == -1))
        ft_error_exit();
}

void ft_son(int *fd, char **argv)
{
    int             entrada;
    char            **cmd1;
    const char      *path;
    int             ex;

    entrada = open(argv[1], O_WRONLY);
    cmd1 = ft_split(argv[2], ' ');
    path = ft_strjoin("/bin/", cmd1[0]);
    close(fd[0]);
    dup2(entrada, STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    ex = execve(path, cmd1, NULL);
    ft_free(cmd1);
    free((void *)path);
    if (ex == -1)
        ft_error_exit();
}

void ft_parent(int *fd, char **argv)
{
    int     salida;
    char    **cmd2;
    const char    *path;
    int     ex;

    salida = open(argv[4], O_WRONLY);
    cmd2 = ft_split(argv[3], ' ');
    path = ft_strjoin("/bin/", cmd2[0]);
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    dup2(salida, STDOUT_FILENO);
    ex = execve(path, cmd2, NULL);
    ft_free(cmd2);
    free((void *)path);
    if (ex == -1)
        ft_error_exit();
}

int main(int argc, char **argv) 
{
    int fd[2];
    int pid;
    int status;

    if (argc != 5)
		return (0);
    ft_check(argv);
    pipe(fd);
    if (pipe(fd) == -1)
        ft_error_exit();
    pid = fork();
    if (pid == -1)
        ft_error_exit();
    if (pid == 0)
        ft_son(fd, argv);
    else
        ft_parent(fd, argv);
    wait(&status);
    return (0);
}
	