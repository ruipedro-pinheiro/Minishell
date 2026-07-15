/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinhier@student.42Lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:36:10 by rpinheir          #+#    #+#             */
/*   Updated: 2026/02/08 17:30:00 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_pipes(t_shell *shell)
{
	shell->pids = malloc(shell->cmd_count * sizeof(pid_t));
	if (!shell->pids)
		exit(1);
	if (shell->cmds->redirections)
	{
		if (shell->cmds->redirections->type == REDIR_HEREDOC)
			return (here_doc_input(shell));
	}
	return (-1);
}

int	parent_update(int prev_fd, int *wread, t_shell *shell)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (shell->cmds->next)
	{
		close(wread[1]);
		return (wread[0]);
	}
	return (-1);
}

int	wait_children(t_shell *shell, int count)
{
	int	i;
	int	status;

	i = -1;
	while (++i < count)
		waitpid(shell->pids[i], &status, 0);
	free(shell->pids);
	waitpid(-1, NULL, 0);
	if (WIFSIGNALED(status))
		return (EXIT_SIGNAL_BASE + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

void	here_doc_read(t_shell *shell, int *wread)
{
	char	*line;
	int		limsize;

	close(wread[0]);
	limsize = ft_strlen(shell->cmds->redirections->file);
	write(1, "heredoc> ", ft_strlen("heredoc> "));
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, shell->cmds->redirections->file, limsize) == 0
			&& ft_strlen(line) == limsize + 1
			&& line[ft_strlen(line) - 1] == '\n')
			break ;
		write(wread[1], line, ft_strlen(line));
		free(line);
		write(1, "heredoc> ", ft_strlen("heredoc> "));
		line = get_next_line(0);
	}
	free(line);
	close(wread[1]);
	close(0);
	get_next_line(0);
	exit(0);
}

int	here_doc_input(t_shell *shell)
{
	int	status;

	if (pipe(shell->wread) == -1)
		exit(1);
	shell->hereid = fork();
	if (shell->hereid == -1)
		exit(1);
	if (shell->hereid == 0)
	{
		set_signal_mode(FORKED);
		here_doc_read(shell, shell->wread);
	}
	waitpid(shell->hereid, &status, 0);
	close(shell->wread[1]);
	if (shell->cmds->redirections->next)
		shell->cmds->redirections = shell->cmds->redirections->next;
	if (WIFSIGNALED(status))
	{
		shell->exit_status = EXIT_SIGNAL_BASE + WTERMSIG(status);
		return (-2);
	}
	else
		shell->exit_status = WEXITSTATUS(status);
	return (shell->wread[0]);
}
