/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinhier@student.42Lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:51:54 by rpinheir          #+#    #+#             */
/*   Updated: 2026/02/04 15:52:15 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		cmds_counter(t_pipex pipex)
{
	int	i;

	i = -1;
	while (pipex.cmds[++i])
		;
	return (i);
}

void	init_pipex(t_pipex *pipex, char *prompt, char **envp)
{
	pipex->envp = envp;
	pipex->limiter = NULL;
	if (ft_strncmp(prompt, "here_doc", 9) == 0)
	{
		pipex->limiter = pipex->cmds[1];
		pipex->infile = NULL;
	}
	else
	{
		pipex->infile = pipex->cmds[0];
	}
	pipex->cmd_count = cmds_counter(*pipex);
	pipex->cmds = ft_split(prompt, ' ');
	pipex->outfile = pipex->cmds[3];
	pipex->pids = NULL;
}

