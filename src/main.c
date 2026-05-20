/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/05/20 18:08:05 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_prompt(t_shell *shell)
{
	int		pid;
	int		status;
	char	*prompt;

	while (true)
	{
		prompt = readline("$: ");
		if (!prompt)
			break ;
		else if (prompt[0])
		{
			debug_cmds(shell->cmds);
			scribe(shell, prompt);
			if (shell->cmds)
				free_cmds(shell->cmds);
			shell->cmds = parse(prompt, shell);
			pid = fork();
			if (pid == 0)
				pipex(shell);
			waitpid(pid, &status, 0);
		}
		free(prompt);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	if (ac > 1 && av[0])
		return (ft_putendl_fd("Arguments are not permitted", 2), 0);
	shell.historian = ft_strdup("");
	historer(&shell);
	if (ac > 1 && av[0])
		return (ft_putendl_fd("Arguments are not permitted", 2), 0);
	shell.historian = ft_strdup("");
	historer(&shell);
	shell.env = env;
	shell.exit_status = 0;
	shell.cmds = NULL;
	set_prompt(&shell);
	if (shell.cmds)
		free_cmds(shell.cmds);
	free(shell.historian);
	return (0);
}
