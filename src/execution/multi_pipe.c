/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinhier@student.42Lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:36:10 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/17 16:41:12 by pedro            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_pipes(t_shell *shell)
{
	t_cmd	*ptr;
	t_redir	*redir;

	ptr = shell->cmds;
	shell->pids = malloc(shell->cmd_count * sizeof(pid_t));
	if (!shell->pids)
		exit(1);
	signal(SIGQUIT, SIG_IGN);
	while (ptr)
	{
		redir = ptr->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
				redir->heredoc_fd
					= here_doc_input(shell, redir);
			redir = redir->next;
		}
		ptr = ptr->next;
	}
	signal(SIGQUIT, SIG_DFL);
	return (-1);
}

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
	while (++i < count)
		waitpid(shell->pids[i], &status, 0);
	free(shell->pids);
	shell->pids = NULL;
	waitpid(-1, NULL, 0);
	if (WIFSIGNALED(status))
		return (EXIT_SIGNAL_BASE + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
