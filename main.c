/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mllamas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:44:45 by mllamas-          #+#    #+#             */
/*   Updated: 2024/01/21 12:07:20 by mllamas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_check_args(int argc, char **argv, char **env)
{
	int		i;
	char	**paths;

	if (argc != 5)
		exit (EXIT_FAILURE);
	if (access(argv[1], R_OK) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

const char	*ft_check_path(char **paths, char *cmd)
{
	int			i;
	const char	*aux;
	const char	*path;

	i = 0;
	while (paths[i] && paths[i] != NULL)
	{
		aux = ft_strjoin(paths[i], "/");
		path = ft_strjoin(aux, cmd);
		free((void *)aux);
		if (access(path, X_OK) == 0)
			return (path);
		free((void *)path);
		i++;
	}
	if (access(cmd, X_OK) == 0)
	{
		return (cmd);
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
	if (paths == NULL)
		path = cmd1[0];
	else
		path = ft_check_path(paths, cmd1[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(entrada, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(entrada);
	ex = execve(path, cmd1, NULL);
	ft_free(cmd1);
	free((void *)path);
	if (ex == -1)
		ft_error_exit(paths);
}

void	ft_son2(int *fd, char **argv, char **paths)
{
	int			salida;
	char		**cmd2;
	const char	*path;
	int			ex;

	salida = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	cmd2 = ft_split(argv[3], ' ');
	if (paths == NULL)
		path = cmd2[0];
	else
		path = ft_check_path(paths, cmd2[0]);
	dup2(fd[0], STDIN_FILENO);
	dup2(salida, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(salida);
	ex = execve(path, cmd2, NULL);
	ft_free(cmd2);
	free((void *)path);
	if (ex == -1)
		ft_error_exit(paths);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	int		pid;
	int		pid2;
	char	**paths;

	paths = ft_check_args(argc, argv, env);
	if (pipe(fd) == -1)
		ft_error_exit(paths);
	pid = fork();
	if (pid < 0)
		ft_error_exit(paths);
	if (pid == 0)
		ft_son(fd, argv, paths);
	pid2 = fork();
	if (pid2 < 0)
		ft_error_exit(paths);
	if (pid2 == 0)
		ft_son2(fd, argv, paths);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
