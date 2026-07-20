/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 17:08:45 by saouissi          #+#    #+#             */
/*   Updated: 2026/05/17 18:19:56 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	cmdlen(t_shell *shell)
{
	t_cmd	*keep;
	int		x;

	x = 0;
	keep = shell->cmds;
	while (shell->cmds->next)
	{
		shell->cmds = shell->cmds->next;
		x++;
	}
	x++;
	shell->cmds = keep;
	return (x);
}

static void	forker(t_shell *shell, int *wread, int x)
{
	if (x == 0)
		startinf(shell, wread);
	if (x != 0 && !shell->cmds->next)
		endoutf(shell, wread);
	else if (x != 0)
		middle(shell, wread);
	exit(2);
}

int	run_pipeline(t_shell *shell)
{
	int		x;
	t_cmd	*keep;

	keep = shell->cmds;
	x = 0;
	while (1)
	{
		if (pipe(shell->wread) == -1)
			exit(1);
		shell->pids[x] = fork();
		if (shell->pids[x] == -1)
			exit(1);
		if (shell->pids[x] == 0)
			forker(shell, shell->wread, x);
		shell->prevfd = parent_update(shell->prevfd, shell->wread, shell);
		x++;
		if (!shell->cmds->next)
			break ;
		shell->cmds = shell->cmds->next;
	}
	shell->cmds = keep;
	(close(shell->wread[0]), close(shell->wread[1]));
	return (wait_children(shell, shell->cmd_count));
}

int	pipex(t_shell *shell)
{
	shell->cmd_count = cmdlen(shell);
	shell->prevfd = init_pipes(shell);
	if (shell->prevfd == -2)
		return (0);
	if (shell->cmds->next == NULL && shell->prevfd == -1)
		return (singlecmd(shell), 0);
	return (run_pipeline(shell));
}
