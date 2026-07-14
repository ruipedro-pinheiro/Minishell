/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:55:50 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/14 18:29:43 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Trying to stop execution after a builtin being executed
void	executor(t_shell *shell)
{
	int	status;
	int	pid;

	set_signal_mode(EXECUTION);
	if (builtex(shell) != -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		set_signal_mode(FORKED);
		pipex(shell);
		destroyer(shell);
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
		prompt = readline("\n" SKY "╭─Minishell──\n╰─❯ " RESET "");
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
			debug_cmds(shell->cmds);
			exit_minishell(shell);
			executor(shell);
		}
		free(prompt);
	}
}
