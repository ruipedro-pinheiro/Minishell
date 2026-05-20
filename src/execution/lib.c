/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:45:42 by saouissi          #+#    #+#             */
/*   Updated: 2026/05/13 18:47:01 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	startinf(t_shell *shell, int *wread)
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

void	middle(t_shell *shell, int *wread)
{
	dup2(shell->prevfd, STDIN_FILENO);
	dup2(wread[1], STDOUT_FILENO);
	close(wread[0]);
	close(wread[1]);
	exec_cmd(shell->cmds->cmd_args, shell->env);
}

void	endoutf(t_shell *shell, int *wread)
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