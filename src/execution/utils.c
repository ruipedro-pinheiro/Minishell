/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:00:38 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/14 19:07:23 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error_handler(char *msg)
{
	perror(msg);
	exit(errno);
}

static char	*pather(t_shell *shell, char *cmd)
{
	int		x;
	int		y;
	char	*all;

	all = dotter(shell, cmd);
	x = ft_strlen(all);
	y = x;
	free(cmd);
	while (all[y] != '/')
		y--;
	cmd = malloc(sizeof(char) * (x - y));
	cmd = ft_strrchr(all, '/');
	cmd = ft_strtrim(cmd, "/");
	return (all);
}

static int	literaler(char *cmd)
{
	int		x;

	x = 0;
	while (cmd[x])
	{
		if (cmd[x] == '/')
			return (1);
		x++;
	}
	return (0);
}

char	*get_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*exec;
	char	*path_part;
	int		i;

	if (literaler(cmd) == 1)
		return (pather(shell, cmd));
	i = -1;
	paths = ft_split(variable_expansion("PATH", shell), ':');
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

	if (bu2(shell) != -1)
		return ;
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
		pexiter(s_cmd, error_msg);
	}
	if (execve(path, s_cmd, envp) == -1)
	{
		perror(s_cmd[0]);
		free(path);
		ft_strfree(s_cmd);
		exit(126);
	}
}
