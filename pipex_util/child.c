/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 04:42:52 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/02 16:50:16 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (!check_cmd(cmd))
		return (NULL);
	path_env = get_path(env);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}

int	check_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_isalpha(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

void	child(char **v, t_data data, char **env)
{
	int		fd;
	char	*path;
	char	*free_check;

	fd = open(v[1], O_RDONLY);
	if (fd == -1)
		error(NULL, NULL, NULL, 1);
	free_check = ft_strtrim(v[2], " ");
	if ((ft_strlen(free_check)) != ft_strlen(v[2]) || !v[2][0])
		(close(fd), error("ERROR: command not found \n", data.cmd, NULL, 0));
	free(free_check);
	data.cmd = ft_split(v[2], ' ');
	path = find_path(data.cmd[0], env);
	if (!path)
		error("ERROR: command not found \n", data.cmd, NULL, 0);
	dup2(fd, 0);
	close(fd);
	close(data.pipefd[0]);
	dup2(data.pipefd[1], 1);
	close(data.pipefd[1]);
	execve(path, data.cmd, env);
	error(NULL, data.cmd, NULL, 1);
}
