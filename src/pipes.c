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

