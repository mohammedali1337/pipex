/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:46:20 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/02 16:49:42 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_error(char **f, char *f2, int x)
{
	int	i;

	i = 0;
	if (x == 1)
	{
		while (f[i])
			free(f[i++]);
		free(f);
	}
	else if (x == 2)
		free(f2);
}

void	error(char *str, char **f, char *f2, int flag)
{
	if (flag)
		perror("Pipex");
	if (str && !flag)
		write(2, str, ft_strlen(str));
	if (f)
		free_error(f, f2, 1);
	if (f2)
		free_error(f, f2, 2);
	exit(1);
}

void	parent(char **v, t_data data, char **env)
{
	int		fd;
	char	**cmd;
	char	*path;
	char	*free_check;

	fd = open(v[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		error(NULL, NULL, NULL, 1);
	free_check = ft_strtrim(v[3], " ");
	if ((ft_strlen(free_check)) != ft_strlen(v[3]) || !v[3][0])
		error("ERROR: command not found \n", data.cmd, NULL, 0);
	free(free_check);
	cmd = ft_split(v[3], ' ');
	path = find_path(cmd[0], env);
	if (!path)
		error("ERROR: command not found \n", cmd, NULL, 0);
	close(data.pipefd[1]);
	(dup2(data.pipefd[0], 0), dup2(fd, 1));
	(close(data.pipefd[0]), close(fd));
	execve(path, cmd, env);
	error(NULL, NULL, NULL, 1);
}

int	main(int c, char **v, char **env)
{
	t_data	data;

	if (c != 5)
		error("invalide number of argument \n", NULL, NULL, 0);
	if (!env)
		error("invalide env\n", NULL, NULL, 0);
	if (pipe(data.pipefd) == -1)
		error(NULL, NULL, NULL, 1);
	data.pid = fork();
	if (data.pid == -1)
		(close(data.pipefd[0]), close(data.pipefd[1]),
			error(NULL, NULL, NULL, 1));
	if (data.pid == 0)
		child(v, data, env);
	data.pid2 = fork();
	if (data.pid2 == -1)
		(close(data.pipefd[0]), close(data.pipefd[1]),
			error(NULL, NULL, NULL, 1));
	if (data.pid2 == 0)
		parent(v, data, env);
	(close(data.pipefd[0]), close(data.pipefd[1]));
	waitpid(data.pid, NULL, 0);
	waitpid(data.pid2, NULL, 0);
	return (0);
}
