/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:55:50 by rpinheir          #+#    #+#             */
/*   Updated: 2026/05/18 19:10:48 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*

*/

// TODO: dispatch builtin parent/child before fork
// (cd/export/unset can't modify parent state inside fork)
void	executor(t_shell *shell)
{
	int	status;
	int	pid;

	set_signal_mode(EXECUTION);
	pid = fork();
	if (pid == 0)
	{
		set_signal_mode(FORKED);
		pipex(shell);
		exit(shell->exit_status);
	}
	waitpid(pid, &status, 0);
	set_signal_mode(INTERACTIVE);
	if (WIFSIGNALED(status))
		shell->exit_status = EXIT_SIGNAL_BASE + WTERMSIG(status);
	else
		shell->exit_status = WEXITSTATUS(status);
}

void	set_prompt(t_shell *shell)
{
	char	*prompt;

	set_signal_mode(INTERACTIVE);
	while (true)
	{
		prompt = readline("$: ");
		if (!prompt)
			break ;
		else if (prompt[0])
		{
			scribe(shell, prompt);
			if (shell->cmds)
				free_cmds(shell->cmds);
			shell->cmds = parse(prompt, shell);
			if (!shell->cmds)
			{
				free(prompt);
				continue ;
			}
			exit_minishell(shell);
			executor(shell);
		}
		free(prompt);
	}
}
