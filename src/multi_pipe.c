/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinhier@student.42Lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:36:10 by rpinheir          #+#    #+#             */
/*   Updated: 2026/02/08 17:30:00 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_pipes(t_pipex *pipex)
{
	pipex->pids = malloc(pipex->cmd_count * sizeof(pid_t));
	if (!pipex->pids)
		exit(1);
	if (pipex->limiter)
		return (here_doc_input(pipex));
	return (-1);
}

void	run_child(t_pipex *pipex, int i, int prev_fd, int *pipe_fd)
{
	if (i == 0 && !pipex->limiter)
		child_start(pipex, pipe_fd);
	else if (i == pipex->cmd_count - 1)
		child_end(pipex, prev_fd);
	else
		child_process(pipex, i, prev_fd, pipe_fd);
}

int	parent_update(int prev_fd, int *pipe_fd, int is_last)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (!is_last)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	return (-1);
}

int	wait_children(t_pipex *pipex)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < pipex->cmd_count)
		waitpid(pipex->pids[i], &status, 0);
	free(pipex->pids);
	waitpid(-1, NULL, 0);
	return (WEXITSTATUS(status));
}

int	pipe_setup(t_pipex *pipex)
{
	int	prev_fd;
	int	i;
	int	pipe_fd[2];

	prev_fd = init_pipes(pipex);
	i = -1;
	while (++i < pipex->cmd_count)
	{
		if (i < pipex->cmd_count - 1 && pipe(pipe_fd) == -1)
			exit(1);
		pipex->pids[i] = fork();
		if (pipex->pids[i] == -1)
			exit(1);
		if (pipex->pids[i] == 0)
			run_child(pipex, i, prev_fd, pipe_fd);
		prev_fd = parent_update(prev_fd, pipe_fd, i == pipex->cmd_count - 1);
	}
	return (wait_children(pipex));
}
