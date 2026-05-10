/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 17:08:45 by saouissi          #+#    #+#             */
/*   Updated: 2026/05/10 18:33:35 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	here_doc_read(t_shell *shell, int *wread)
{
	char	*prompt;
	int		pid;
	int		status;

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
				break ;
			pid = fork();
			if (pid == 0)
				write(wread[1], prompt, ft_strlen(prompt));
			waitpid(pid, &status, 0);
		}
		free(prompt);
	}
	close(wread[1]);
}

static void	startinf(t_shell *shell, int *wread)
{
	int	fd;

	if (shell->cmds->redirections)
	{
		if (shell->cmds->redirections->type == REDIR_IN)
		{
			fd = open(shell->cmds->redirections->file, O_RDONLY, 0);
			if (fd == -1)
				exit(1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	dup2(wread[1], STDOUT_FILENO);
	close(wread[0]);
	close(wread[1]);
	exec_cmd(shell->cmds->cmd_args, shell->env);
}

static void	middle(t_shell *shell, int *wread)
{
	dup2(shell->prevfd, STDIN_FILENO);
	dup2(wread[1], STDOUT_FILENO);
	close(wread[0]);
	close(wread[1]);
	exec_cmd(shell->cmds->cmd_args, shell->env);
}

static void	endoutf(t_shell *shell, int *wread)
{
	int	fd;

	if (shell->cmds->redirections)
	{
		if (shell->cmds->redirections->type == REDIR_OUT || shell->cmds->redirections->type == REDIR_APPEND)
		{
			if (shell->cmds->redirections->type == REDIR_APPEND)
				fd = open(shell->cmds->redirections->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd = open(shell->cmds->redirections->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
				exit(1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
	dup2(shell->prevfd, STDIN_FILENO);
	close(wread[0]);
	close(wread[1]);
	exec_cmd(shell->cmds->cmd_args, shell->env);
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
	if (shell->cmds->next == NULL && shell->cmds->redirections->type != REDIR_HEREDOC)
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

void	singlecmd(t_shell *shell)
{
	int	fd;
	int	fd2;

	if (!shell->cmds->redirections)
		return (exec_cmd(shell->cmds->cmd_args, shell->env));
	if (shell->cmds->redirections->type == REDIR_IN)
	{
		fd = open(shell->cmds->redirections->file, O_RDONLY, 0);
		if (fd == -1)
			exit(1);
		(dup2(fd, STDIN_FILENO), close(fd));
		if (shell->cmds->redirections->next)
			shell->cmds->redirections = shell->cmds->redirections->next;
	}
	if (shell->cmds->redirections->type == REDIR_OUT || shell->cmds->redirections->type == REDIR_APPEND)
	{
		if (shell->cmds->redirections->type == REDIR_APPEND)
			fd2 = open(shell->cmds->redirections->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd2 = open(shell->cmds->redirections->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			exit(1);
		(dup2(fd2, STDOUT_FILENO), close(fd2));
	}
	exec_cmd(shell->cmds->cmd_args, shell->env);
}
