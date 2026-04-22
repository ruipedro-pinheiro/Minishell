/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/21 22:06:18 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_shell *shell, char **env)
{
	int	pid;
	int	i;

	i = 0;
	pid = 0;
	if (pid == 0)
		exec_cmd(shell->cmds->cmd_args, env);
}

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
			debug_cmds(shell->cmds);
			pid = fork();
			if (pid == 0)
				execute(shell, shell->env);
			waitpid(pid, &status, 0);
		}
		prompt = readline("$: ");
		if (!prompt)
			break ;
		scribe(shell, prompt);
		if (shell->cmds)
			free_cmds(shell->cmds);
		shell->cmds = parse(prompt, shell);
		free(prompt);
		//exiter is now on parser. if prompt contains exit in it, it will exit
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	shell.historian = ft_strdup("");
	historer(&shell);
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
///*Two arguments made of a command and an infile*/

///*Two arguments made of a command and an outfile*/
//
//void	twoargoutfile(char **argv, char **env)
//{
//	int	fd;
//
//	fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (fd == -1)
//		exit(1);
//	dup2(fd, STDOUT_FILENO);
//	close(fd);
//	exec_cmd(argv[2], env);
//}
//
///*Two arguments made of two commands and a pipe*/
//
//static void	child(char **argv, int *wread, char **env)
//{
//	dup2(wread[1], STDOUT_FILENO);
//	close(wread[0]);
//	close(wread[1]);
//	exec_cmd(argv[1], env);
//}
//
//static void	parent(char **argv, int *wread, char **env)
//{
//	dup2(wread[0], STDIN_FILENO);
//	close(wread[0]);
//	close(wread[1]);
//	exec_cmd(argv[2], env);
//}
//
//int	twoargpipe(char **argv, char **env)
//{
//	int		wread[2];
//	pid_t	pid1;
//	pid_t	pid2;
//	int		status;
//
//	if (pipe(wread) == -1)
//		exit(-1);
//	pid1 = fork();
//	if (pid1 == -1)
//		exit(-1);
//	if (pid1 == 0)
//		child(argv, wread, env);
//	pid2 = fork();
//	if (pid2 == -1)
//		exit(-1);
//	if (pid2 == 0)
//		parent(argv, wread, env);
//	(close(wread[0]), close(wread[1]));
//	(waitpid(pid1, NULL, 0), waitpid(pid2, &status, 0));
//	return (0);
//}
//
///*Two arguments made of two commands, a pipe and an infile*/
//
//static void	child2(char **argv, int *wread, char **env)
//{
//	int	fd;
//
//	fd = open(argv[1], O_RDONLY, 0);
//	if (fd == -1)
//		exit(1);
//	dup2(fd, STDIN_FILENO);
//	dup2(wread[1], STDOUT_FILENO);
//	close(fd);
//	close(wread[0]);
//	close(wread[1]);
//	exec_cmd(argv[2], env);
//}
//
//static void	parent2(char **argv, int *wread, char **env)
//{
//	dup2(wread[0], STDIN_FILENO);
//	close(wread[0]);
//	close(wread[1]);
//	exec_cmd(argv[3], env);
//}
//
//int	threeargin(char **argv, char **env)
//{
//	int		wread[2];
//	pid_t	pid1;
//	pid_t	pid2;
//	int		status;
//
//	if (pipe(wread) == -1)
//		exit(-1);
//	pid1 = fork();
//	if (pid1 == -1)
//		exit(-1);
//	if (pid1 == 0)
//		child2(argv, wread, env);
//	pid2 = fork();
//	if (pid2 == -1)
//		exit(-1);
//	if (pid2 == 0)
//		parent2(argv, wread, env);
//	(close(wread[0]), close(wread[1]));
//	(waitpid(pid1, NULL, 0), waitpid(pid2, &status, 0));
//	return (0);
//}
//
///*Two arguments made of two commands, a pipe and an outfile*/
//
//static void	child3(char **argv, int *wread, char **env)
//{
//	dup2(wread[1], STDOUT_FILENO);
//	close(wread[0]);
//	close(wread[1]);
//	exec_cmd(argv[2], env);
//}
//
//static void	parent3(char **argv, int *wread, char **env)
//{
//	int	fd;
//
//	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
//	if (fd == -1)
//		exit(1);
//	dup2(wread[0], STDIN_FILENO);
//	dup2(fd, STDOUT_FILENO);
//	close(fd);
//	close(wread[0]);
//	close(wread[1]);
//	exec_cmd(argv[3], env);
//}
//
//int	threeargout(char **argv, char **env)
//{
//	int		wread[2];
//	pid_t	pid1;
//	pid_t	pid2;
//	int		status;
//
//	if (pipe(wread) == -1)
//		exit(-1);
//	pid1 = fork();
//	if (pid1 == -1)
//		exit(-1);
//	if (pid1 == 0)
//		child3(argv, wread, env);
//	pid2 = fork();
//	if (pid2 == -1)
//		exit(-1);
//	if (pid2 == 0)
//		parent3(argv, wread, env);
//	(close(wread[0]), close(wread[1]));
//	(waitpid(pid1, NULL, 0), waitpid(pid2, &status, 0));
//	return (0);
//}
