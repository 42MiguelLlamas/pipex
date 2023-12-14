#include "pipex.h"

void ft_check_args(char **argv)
{
    if (access(argv[1], R_OK == -1))
        ft_error_exit();
    if (access(argv[4], W_OK == -1))
        ft_error_exit();
}

const char    *ft_check_path(char **paths, char *cmd)
{
    int i;
    const char *aux;
    const char *path;

    i = 0;
    if (access(cmd, X_OK) == 0)
        return (cmd);
    while (paths[i])
    {
        aux = ft_strjoin(paths[i], "/");
        path = ft_strjoin(aux, cmd);
        free((void *)aux);
        if (access(path, X_OK) == 0)
            return(path);
        free((void *)path);
        i++;
    }
    write(1, "Error: Command not found\n", 25);
    exit(EXIT_FAILURE);
}
void ft_son(int *fd, char **argv, char **paths)
{
    int             entrada;
    char            **cmd1;
    const char      *path;
    int             ex;

    entrada = open(argv[1], O_WRONLY);
    cmd1 = ft_split(argv[2], ' ');
    path = ft_check_path(paths, cmd1[0]);
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

void ft_parent(int *fd, char **argv, char **paths)
{
    int     salida;
    char    **cmd2;
    int     ex;
    const char    *path;

    salida = open(argv[4], O_WRONLY);
    cmd2 = ft_split(argv[3], ' ');
    path = ft_check_path(paths, cmd2[0]);
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    dup2(salida, STDOUT_FILENO);
    close(fd[0]);
    ex = execve(path, cmd2, NULL);
    ft_free(cmd2);
    free((void *)path);
    if (ex == -1)
        ft_error_exit();
}

int main(int argc, char **argv, char **envp) 
{
    int fd[2];
    int pid;
    int status;
    int i;
    char **paths;

    if (argc != 5)
		return (0);
    ft_check_args(argv);
    i = 0;
    while (ft_strncmp("PATH=", envp[i], 5) != 0)
        i++;
    paths = ft_split(envp[i] + 5, ':');
    if (pipe(fd) == -1)
        ft_error_exit();
    pid = fork();
    if (pid == -1)
        ft_error_exit();
    if (pid == 0)
        ft_son(fd, argv, paths);
    else
        ft_parent(fd, argv, paths);
    wait(&status);
    return (0);
}
