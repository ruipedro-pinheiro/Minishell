/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 17:08:45 by saouissi          #+#    #+#             */
/*   Updated: 2026/05/13 18:46:50 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	here_doc_read(t_shell *shell, int *wread)
{
	char	*prompt;
	int		pid;
	int		status;

	// dup2(wread[0], STDIN_FILENO);
	close(wread[0]);
	// dup2(wread[1], STDOUT_FILENO);
	while (true)
	{
		prompt = readline("heredoc> ");
		if (!prompt)
			break;
		else if (prompt[0])
		{
			if (ft_strcmp(prompt, shell->cmds->redirections->file) == 0)
				return ;
			pid = fork();
			if (pid == 0)
				write(wread[1], prompt, ft_strlen(prompt));
			waitpid(pid, &status, 0);
		}
		free(prompt);
	}
	close(wread[1]);
}

static int	cmdlen(t_cmd *cmd)
{
	t_cmd *keep;
	int	x;

	x = 0;
	keep = cmd;
	while (cmd->next)
	{
		cmd = cmd->next;
		x++;
	}
	x++;
	cmd = keep;
	return (x);
}

static void	forker(t_shell *shell, int *wread, int x)
{
	if (x == 0 && shell->cmds->redirections)
	{
		if (shell->cmds->redirections->type == REDIR_HEREDOC)
		{
			if (!shell->cmds->next)
				endoutf(shell, wread);
			else
				middle(shell, wread);
			return ;
		}
	}
	if (x == 0)
		startinf(shell, wread);
	if (x != 0 && !shell->cmds->next)
		endoutf(shell, wread);
	else if (x != 0)
		middle(shell, wread);
}

int	pipex(t_shell *shell, t_cmd *cmds)
{
	int x;

	shell->cmd_count = cmdlen(cmds);
	x = 0;
	shell->prevfd = init_pipes(shell);
	waitpid(shell->hereid, NULL, 0);
	if (shell->cmds->next == NULL && shell->prevfd == -1)
		return (singlecmd(shell), 0);
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
	(close(shell->wread[0]), close(shell->wread[1]));
	return (wait_children(shell, shell->cmd_count));
}
