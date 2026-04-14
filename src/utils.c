/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:00:38 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/14 16:30:05 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->envp = envp;
	pipex->limiter = NULL;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		pipex->limiter = argv[2];
		pipex->cmds = &argv[3];
		pipex->cmd_count = argc - 4;
		pipex->infile = NULL;
	}
	else
	{
		pipex->cmds = &argv[2];
		pipex->cmd_count = argc - 3;
		pipex->infile = argv[1];
	}
	pipex->outfile = argv[argc - 1];
	pipex->pids = NULL;
}

int	error_handler(char *msg)
{
	perror(msg);
	exit(errno);
}

char	*get_path(char *cmd)
{
	char	**paths;
	char	*exec;
	char	*path_part;
	int		i;

	i = 0;
	paths =  ft_split(getenv("PATH"), ':');
	if (!paths)
		exit(0);
	while (paths[i])
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
		i++;
	}
	ft_strfree(paths);
	return (NULL);
}

static void	trimmer(char **a)
{
	int		x;
	char	*b;

	x = 0;
	while (a[x])
	{
		if (a[x][0] == '\'')
		{
			b = ft_strtrim(a[x], "\'");
			a[x] = b;
		}
		x++;
	}
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;
	char	*error_msg;

	s_cmd = ft_split(cmd, ' ');
	trimmer(s_cmd);
	path = get_path(s_cmd[0]);
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
