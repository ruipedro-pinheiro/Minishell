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

#include "../../include/minishell.h"

int	init_pipes(t_shell *shell)
{
	shell->pids = malloc(shell->cmd_count * sizeof(pid_t));
	if (!shell->pids)
		exit(1);
	if (shell->cmds->redirections)
	{
		if (shell->cmds->redirections->type == REDIR_HEREDOC)
			return (here_doc_input(shell));
	}
	return (-1);
}

// void	run_child(t_shell *shell, int i, int prev_fd, int *pipe_fd)
// {
// 	if (i == 0 && shell->cmds->redirections->type != REDIR_HEREDOC)
// 		child_start(shell, pipe_fd);
// 	else if (i == shell->cmd_count - 1)
// 		child_end(shell, prev_fd);
// 	else
// 		child_process(shell, i, prev_fd, pipe_fd);
// }

int	parent_update(int prev_fd, int *wread, t_shell *shell)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (shell->cmds->next)
	{
		close(wread[1]);
		return (wread[0]);
	}
	return (-1);
}

int	wait_children(t_shell *shell, int count)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < count)
		waitpid(shell->pids[i], &status, 0);
	free(shell->pids);
	waitpid(-1, NULL, 0);
	return (WEXITSTATUS(status));
}

// int	pipe_setup(t_shell *shell)
// {
// 	int	prev_fd;
// 	int	i;
// 	int	pipe_fd[2];
// 	int	count; //

// 	count = 0; //
// 	prev_fd = init_pipes(shell);
// 	i = -1;
// 	while (++i < shell->cmd_count)
// 	{
// 		if (i < shell->cmd_count - 1 && pipe(pipe_fd) == -1)
// 			exit(1);
// 		shell->pids[i] = fork();
// 		if (shell->pids[i] == -1)
// 			exit(1);
// 		if (shell->pids[i] == 0)
// 			run_child(shell, i, prev_fd, pipe_fd);
// 		prev_fd = parent_update(prev_fd, pipe_fd, i == shell->cmd_count - 1);
// 	}
// 	return (wait_children(shell, count)); //
// }
