/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/17 17:28:50 by saouissi         ###   ########.fr       */
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
		if (prompt[0])
		{
			pid = fork();
			if (pid == 0)
				//execute(shell->cmds, shell);
				exec_cmd(prompt, shell->env); // replace by parser + execution
			waitpid(pid, &status, 0);
		}
		prompt = readline("$: ");
		shell->historian = ft_strjoin(shell->historian, prompt);
		shell->historian = ft_strjoin(shell->historian, "\n");
		exiter(shell); // remove/comment for testings, to be moved within the parser/whatever else (exit command and ctrl-D). only here for testing
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	char	*a;
	int		fd;

	shell.historian = ft_strdup(""); // VERY prone to leaks, only here as a placeholder
	fd = open(".minishell_history", O_RDONLY); //
	if (fd > 0) //
	{ //
		while ((a = get_next_line(fd))) //
		{
			shell.historian = ft_strjoin(shell.historian, a); //
			free(a);
		}
	} //
	close(fd); //until here
	if (av[0][0] == '\0')
		return (0);
	shell.env = env;
	shell.exit_status = 0;
	shell.cmds = NULL;
	if (ac > 1)
		return (pipex(ac, av, &shell));
	set_prompt(&shell);
	return (0);
}

int	pipex(int ac, char **av, t_shell *shell)
{
	if (ac == 2)
		exec_cmd(av[1], shell->env);
	if (ac == 3)
		parent(av, shell->env);
	if (ac >= 4)
	{
		if (ft_strncmp(av[1], "here_doc", 9) == 0 && ac < 6)
			return (ft_putstr_fd("Error: bad arguments\n", 2), 1);
		init_pipex(shell, ac, av, shell->env);
	}
	return (pipe_setup(shell));
}

void	parent(char **argv, char **env)
{
	int	fd;

	fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	exec_cmd(argv[2], env);
}
