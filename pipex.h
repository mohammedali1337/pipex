/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:44:58 by mgarouj           #+#    #+#             */
/*   Updated: 2025/02/25 10:31:54 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "pipex.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_data
{
	int		pipefd[2];
	pid_t	pid;
	int		pid2;
	int		fd;
	char	**cmd;
	char	*path;
}			t_data;
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	child(char **v, t_data *data, char **env);
void	error(char *str, char **f, char *f2);
int		ft_strlen(const char *s);
char	*find_path(char *cmd, char **env);
int		check_cmd(char *cmd);
int		ft_isalpha(int c);
#endif