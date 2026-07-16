/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:45:42 by saouissi          #+#    #+#             */
/*   Updated: 2026/07/15 19:53:18 by pedro            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	startinf(t_shell *shell, int *wread)
{
	dup2(wread[1], STDOUT_FILENO);
	close(wread[0]);
	close(wread[1]);
	if (apply_redirs(shell) == -1)
		exit(1);
	exec_cmd(shell->cmds->cmd_args, shell->env, shell);
}

void	middle(t_shell *shell, int *wread)
{
	dup2(shell->prevfd, STDIN_FILENO);
	dup2(wread[1], STDOUT_FILENO);
	close(wread[0]);
	close(wread[1]);
	if (apply_redirs(shell) == -1)
		exit(1);
	exec_cmd(shell->cmds->cmd_args, shell->env, shell);
}

void	endoutf(t_shell *shell, int *wread)
{
	dup2(shell->prevfd, STDIN_FILENO);
	close(wread[0]);
	close(wread[1]);
	if (apply_redirs(shell) == -1)
		exit(1);
	exec_cmd(shell->cmds->cmd_args, shell->env, shell);
}

void	singlecmd(t_shell *shell)
{
	if (!shell->cmds->redirections)
		return (exec_cmd(shell->cmds->cmd_args, shell->env, shell));
	if (apply_redirs(shell) == -1)
		exit(1);
	exec_cmd(shell->cmds->cmd_args, shell->env, shell);
}
