/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:00:38 by rpinheir          #+#    #+#             */
/*   Updated: 2026/06/03 19:16:27 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error_handler(char *msg)
{
	perror(msg);
	exit(errno);
}

static char	*literaler(char *cmd)
{
	int		x;
	int		y;
	char	*all;

	x = ft_strlen(cmd);
	y = x;
	all = ft_strdup(cmd);
	free(cmd);
	while (all[y] != '/')
		y--;
	cmd = malloc(sizeof(char) * (x - y));
	cmd = ft_strrchr(all, '/');
	cmd = ft_strtrim(cmd, "/");
	return (all);
}

char	*get_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*exec;
	char	*path_part;
	int		i;

	if (cmd[0] == '/' || cmd[0] == '.')
		return (literaler(cmd));
	i = -1;
	paths = ft_split(value_extraction("PATH", shell), ':');
	if (!paths)
		exit(0);
	while (paths[++i])
	{
		path_part = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, X_OK) == 0)
		{
			ft_strfree(paths);
			return (exec);
		}
		free(exec);
	}
	ft_strfree(paths);
	return (NULL);
}

void	exec_cmd(char **s_cmd, char **envp, t_shell *shell)
{
	char	*path;
	char	*error_msg;

	if (!s_cmd || !s_cmd[0])
	{
		ft_putstr_fd(s_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	path = get_path(s_cmd[0], shell);
	if (!path)
	{
		error_msg = ft_strjoin(*s_cmd, ": command not found\n");
		ft_putstr_fd(error_msg, 2);
		ft_strfree(s_cmd);
		free(error_msg);
		exit(127);
	}
	if (execve(path, s_cmd, envp) == -1)
	{
		perror(s_cmd[0]);
		free(path);
		ft_strfree(s_cmd);
		exit(126);
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	x;

	x = 0;
	while (s1[x] || s2[x])
	{
		if (s1[x] != s2[x])
			return (s1[x] - s2[x]);
		x++;
	}
	return (0);
}
