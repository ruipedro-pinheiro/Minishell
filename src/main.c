/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/23 18:09:37 by saouissi         ###   ########.fr       */
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
			break;
		else if (prompt[0])
		{
			debug_cmds(shell->cmds);
			scribe(shell, prompt);
			if (shell->cmds)
				free_cmds(shell->cmds);
			shell->cmds = parse(prompt, shell);
			pid = fork();
			if (pid == 0)
				exec_cmd(shell->cmds->cmd_args, shell->env);
			waitpid(pid, &status, 0);
		}
		free(prompt);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	historer(&shell);
	shell.historian = ft_strdup("");
	shell.env = env;
	shell.exit_status = 0;
	shell.cmds = NULL;
	if (ac > 1)
		return (pipex(ac, av, &shell));
	set_prompt(&shell);
	if (shell.cmds)
		free_cmds(shell.cmds);
	free(shell.historian);
	return (0);
}

void	twoarginfile(char **cmd_args, char **env)
{
	int	fd;

	fd = open(cmd_args[2], O_RDONLY);
	if (fd == -1)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	exec_cmd(&cmd_args[2], env);
}

int	pipex(int ac, char **av, t_shell *shell)
{
	exec_cmd(shell->cmds->cmd_args, shell->env);
	twoarginfile(shell->cmds->cmd_args, shell->env);
		if (ft_strncmp(av[1], "here_doc", 9) == 0 && ac < 6)
			return (ft_putstr_fd("Error: bad arguments\n", 2), 1);
		init_pipex(shell, ac, av, shell->env);
	return (pipe_setup(shell));
}

// void	singlecmd(char **argv, int *wread, char **env)
// {
// 	int	fd;
// 	int	fd2;

// 	fd = open(argv[1], O_RDONLY, 0);
// 	if (fd == -1)
// 		exit(1);
// 	fd2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	dup2(fd, STDIN_FILENO);
// 	dup2(fd2, STDOUT_FILENO);
// 	close(fd);
// 	close(fd2);
// 	exec_cmd(argv, env);
// }

// void	startno(char **argv, int *wread, char **env)
// {
// 	dup2(wread[1], STDOUT_FILENO);
// 	close(wread[0]);
// 	close(wread[1]);
// 	exec_cmd(argv, env);
// }

// void	endno(char **argv, int *wread, char **env)
// {
// 	dup2(wread[0], STDIN_FILENO);
// 	close(wread[0]);
// 	close(wread[1]);
// 	exec_cmd(argv, env);
// }

// void	middle(char **argv, int *wread, char **env)
// {
// 	dup2(wread[0], STDIN_FILENO);
// 	dup2(wread[1], STDOUT_FILENO);
// 	close(wread[0]);
// 	close(wread[1]);
// 	exec_cmd(argv, env);
// }

// void	startinf(char **argv, int *wread, char **env)
// {
// 	int	fd;

// 	fd = open(argv[1], O_RDONLY, 0);
// 	if (fd == -1)
// 		exit(1);
// 	dup2(fd, STDIN_FILENO);
// 	dup2(wread[1], STDOUT_FILENO);
// 	close(fd);
// 	close(wread[0]);
// 	close(wread[1]);
// 	exec_cmd(argv, env);
// }

// void	endoutf(char **argv, int *wread, char **env)
// {
// 	int	fd;

// 	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd == -1)
// 		exit(1);
// 	dup2(wread[0], STDIN_FILENO);
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	close(wread[0]);
// 	close(wread[1]);
// 	exec_cmd(argv, env);
// }
