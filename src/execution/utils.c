/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:00:38 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/20 18:14:09 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_pipex(t_shell *shell, int argc, char **argv, char **envp)
{
	shell->env = envp;
	shell->limiter = NULL;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		shell->limiter = argv[2];
		shell->cmds->cmd_args = &argv[3];
		shell->cmd_count = argc - 4;
		shell->infile = NULL;
	}
	else
	{
		shell->cmds->cmd_args = &argv[2];
		shell->cmd_count = argc - 3;
		shell->infile = argv[1];
	}
	shell->outfile = argv[argc - 1];
	shell->pids = NULL;
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
	paths = ft_split(getenv("PATH"), ':');
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

//static void	trimmer(char **a)
//{
//	int		x;
//	char	*b;
//
//	x = 0;
//	while (a[x])
//	{
//		if (a[x][0] == '\'')
//		{
//			b = ft_strtrim(a[x], "\'");
//			a[x] = b;
//		}
//		x++;
//	}
//}

//void	exec_cmd(char **cmd, char **envp)
// removed strfree, it is already freed by free_cmds in the main
void	exec_cmd(char **s_cmd, char **envp)
{
	char	*path;
	char	*error_msg;

	if (!s_cmd || !s_cmd[0])
	{
		ft_putstr_fd(s_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
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

// void	exec_cmd(char **s_cmd, char **envp)
// {
// 	char	*path;
// 	char	*error_msg;

// 	path = get_path(s_cmd[0]);
// 	if (!path)
// 	{
// 		error_msg = ft_strjoin(*s_cmd, ": command not found\n");
// 		ft_putstr_fd(error_msg, 2);
// 		ft_strfree(s_cmd);
// 		free(error_msg);
// 		exit(127);
// 	}
// 	if (execve(path, s_cmd, envp) == -1)
// 	{
// 		perror(s_cmd[0]);
// 		free(path);
// 		ft_strfree(s_cmd);
// 		exit(126);
// 	}
// }
