/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mllamas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:44:45 by mllamas-          #+#    #+#             */
/*   Updated: 2023/12/15 11:55:40 by mllamas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_args(char **argv)
{
	if (access(argv[1], R_OK == -1))
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (access(argv[4], W_OK == -1))
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

const char	*ft_check_path(char **paths, char *cmd)
{
	int			i;
	const char	*aux;
	const char	*path;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (paths[i])
	{
		aux = ft_strjoin(paths[i], "/");
		path = ft_strjoin(aux, cmd);
		free((void *)aux);
		if (access(path, X_OK) == 0)
			return (path);
		free((void *)path);
		i++;
	}
	write(1, "Error: Command not found\n", 25);
	ft_free(paths);
	exit(EXIT_FAILURE);
}

void	ft_son(int *fd, char **argv, char **paths)
{
	int			entrada;
	char		**cmd1;
	const char	*path;
	int			ex;

	entrada = open(argv[1], O_RDONLY);
	cmd1 = ft_split(argv[2], ' ');
	path = ft_check_path(paths, cmd1[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(entrada, STDIN_FILENO);
	close(fd[0]);
	ex = execve(path, cmd1, NULL);
	ft_free(cmd1);
	free((void *)path);
	if (ex == -1)
		ft_error_exit(paths);
}

void	ft_parent(int *fd, char **argv, char **paths)
{
	int			salida;
	char		**cmd2;
	int			ex;
	const char	*path;

	salida = open(argv[4], O_WRONLY);
	cmd2 = ft_split(argv[3], ' ');
	path = ft_check_path(paths, cmd2[0]);
	dup2(fd[0], STDIN_FILENO);
	dup2(salida, STDOUT_FILENO);
	close(fd[1]);
	ex = execve(path, cmd2, NULL);
	ft_free(cmd2);
	free((void *)path);
	if (ex == -1)
		ft_error_exit(paths);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid;
	int		i;
	char	**paths;

	if (argc != 5)
		return (0);
	ft_check_args(argv);
	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (pipe(fd) == -1)
		ft_error_exit(paths);
	pid = fork();
	if (pid < 0)
		ft_error_exit(paths);
	else if (pid == 0)
		ft_son(fd, argv, paths);
	waitpid(pid, NULL, 0);
	ft_parent(fd, argv, paths);
	return (0);
}
