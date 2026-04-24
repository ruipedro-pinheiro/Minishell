/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/24 18:08:59 by saouissi         ###   ########.fr       */
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
				pipex(shell, shell->cmds);
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
	useless(ac, av); // useless, just here to silence the unused av and ac warning
	// if (ac > 1)
	// 	return (pipex(&shell, &shell->cmd));
	set_prompt(&shell);
	if (shell.cmds)
		free_cmds(shell.cmds);
	free(shell.historian);
	return (0);
}

void useless(int ac, char **av)
{
	ac = 1;
	if (ac == 1)
		av[0] = "hey";
	
}
// void	twoarginfile(char **cmd_args, char **env)
// {
// 	int	fd;

// 	fd = open(cmd_args[2], O_RDONLY);
// 	if (fd == -1)
// 		exit(1);
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// 	exec_cmd(&cmd_args[2], env);
// }
static int	edgex(t_shell *shell, t_cmd *cmds)
{
	if (cmds->redirections == NULL)
		exec_cmd(cmds->cmd_args, shell->env);
	if (cmds->redirections)
		singlecmd(shell);
	return (0);
}

int	pipex(t_shell *shell, t_cmd *cmds)
{
	if (cmds->next == NULL)
	{
		edgex(shell, cmds);
		return (0);
	}
	// while (shell->cmds != NULL)
	// {
	// 	if ()
	// }
	return (0);
}

void	singlecmd(t_shell *shell)
{
	int	fd;
	int	fd2;

	if (shell->cmds->redirections->type == REDIR_IN)
	{
		fd = open(shell->cmds->redirections->file, O_RDONLY, 0);
		if (fd == -1)
			exit(1);
		dup2(fd, STDIN_FILENO);
		close(fd);
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
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
	}
	exec_cmd(shell->cmds->cmd_args, shell->env);
}

// void	startno(t_shell *shell, int *wread, char **env)
// {
// 	dup2(wread[1], STDOUT_FILENO);
// 	close(wread[0]);
// 	close(wread[1]);
// 	exec_cmd(argv, shell->env);
// }

// void	endno(t_shell *shell, int *wread, char **env)
// {
// 	dup2(wread[0], STDIN_FILENO);
// 	close(wread[0]);
// 	close(wread[1]);
// 	exec_cmd(argv, shell->env);
// }

// void	middle(t_shell *shell, int *wread, char **env)
// {
// 	dup2(wread[0], STDIN_FILENO);
// 	dup2(wread[1], STDOUT_FILENO);
// 	close(wread[0]);
// 	close(wread[1]);
// 	exec_cmd(argv, shell->env);
// }

// void	startinf(t_shell *shell, int *wread, char **env)
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
// 	exec_cmd(argv, shell->env);
// }

// void	endoutf(t_shell *shell, int *wread, char **env)
// {
// 	int	fd;

// 	if (shell->cmds->redirections)
// 		fd = open(argv[4], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else
// 		fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd == -1)
// 		exit(1);
// 	dup2(wread[0], STDIN_FILENO);
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	close(wread[0]);
// 	close(wread[1]);
// 	exec_cmd(argv, shell->env);
// }
