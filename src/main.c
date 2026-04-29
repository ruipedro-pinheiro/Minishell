/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/29 18:45:31 by saouissi         ###   ########.fr       */
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
		write(1, av[0], 1);
}

static void	startinf(t_shell *shell, int *wread)
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

static void	middle(t_shell *shell, int *wread)
{
	dup2(shell->prevfd, STDIN_FILENO);
	dup2(wread[1], STDOUT_FILENO);
	close(wread[0]);
	close(wread[1]);
	exec_cmd(shell->cmds->cmd_args, shell->env);
}

static void	endoutf(t_shell *shell, int *wread)
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

// static void	endoutf2(t_shell *shell, int *wread)
// {
// 	int	fd;

// 	if (shell->cmds->redirections->type == REDIR_OUT || shell->cmds->redirections->type == REDIR_APPEND)
// 	{
// 		if (shell->cmds->redirections->type == REDIR_APPEND)
// 			fd = open(shell->cmds->redirections->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		else
// 			fd = open(shell->cmds->redirections->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 		if (fd == -1)
// 			exit(1);
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// 	dup2(wread[1], STDIN_FILENO);
// 	close(wread[0]);
// 	close(wread[1]);
// 	exec_cmd(shell->cmds->cmd_args, shell->env);
// }

static int	cmdlen(t_cmd *cmd)
{
	t_cmd *keep;
	int	x;

	x = 0;
	keep = cmd;
	while (cmd->next)
	{
		cmd = cmd->next;
		x++;
	}
	x++;
	cmd = keep;
	return (x);
}

static void	forker(t_shell *shell, int *wread, int x)
{
	if (x == 0)
		startinf(shell, wread);
	if (x != 0 && !shell->cmds->next)
		endoutf(shell, wread);
	else if (x != 0)
		middle(shell, wread);
}

// static int	px_status_to_exitcode(int status)
// {
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	if (WIFSIGNALED(status))
// 		return (128 + WTERMSIG(status));
// 	return (1);
// }

static int	wait_children(t_shell *shell, int count) //
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < count)
		waitpid(shell->pids[i], &status, 0);
	free(shell->pids);
	waitpid(-1, NULL, 0);
	return (WEXITSTATUS(status));
}

static int	parent_update(int prev_fd, int *pipe_fd, t_shell *shell)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (shell->cmds->next)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	return (-1);
}

int	pipex(t_shell *shell, t_cmd *cmds)
{
	int	wread[2];
	int x;

	shell->cmd_count = cmdlen(cmds);
	x = 0;
	if (cmds->next == NULL)
		return (singlecmd(shell), 0);
	shell->pids = malloc(sizeof(pid_t) * cmdlen(cmds));
	while (1)
	{
		if (pipe(wread) == -1)
			exit(1);
		shell->pids[x] = fork();
		if (shell->pids[x] == -1)
			exit(1);
		if (shell->pids[x] == 0)
			forker(shell, wread, x);
		shell->prevfd = parent_update(shell->prevfd, wread, shell);
		x++;
		if (!shell->cmds->next)
			break ;
		shell->cmds = shell->cmds->next;
	}
	(close(wread[0]), close(wread[1]));
	return (wait_children(shell, shell->cmd_count));
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

