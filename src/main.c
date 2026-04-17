/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/15 12:36:36 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_prompt(t_shell *shell)
{
	int		pid;
	int		status;
	char	*prompt;

	prompt = "";
	while (true)
	{
		pid = fork();
		if (pid == 0)
		{
			shell->cmds = parse(prompt);
			//execute(shell->cmds, shell);
			exec_cmd(prompt, shell->env); // replace by parser + execution
		}

		waitpid(pid, &status, 0);
		prompt = readline("$: ");
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	if (av[0][0] == '\0')
		return (0);
	shell.env = env;
	shell.exit_status = 0;
	shell.cmds = NULL;
	if (ac > 1)
		return (pipex(ac, av, env));
	set_prompt(&shell);
	return (0);
}

int	pipex(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac == 2)
		exec_cmd(av[1], env);
	if (ac == 3)
		parent(av, env);
	if (ac >= 4)
	{
		if (ft_strncmp(av[1], "here_doc", 9) == 0 && ac < 6)
			return (ft_putstr_fd("Error: bad arguments\n", 2), 1);
		init_pipex(&pipex, ac, av, env);
	}
	return (pipe_setup(&pipex));
}

void	parent(char **argv, char **env)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	exec_cmd(argv[2], env);
}
