/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinhier@student.42Lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:30:00 by rpinheir          #+#    #+#             */
/*   Updated: 2026/02/08 17:30:00 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	here_doc_read(t_shell *shell, int *shell->wread)
// {
// 	char	*line;
// 	int		len;

// 	close(shell->wread[0]);
// 	len = ft_strlen(shell->cmds->redirections->file);
// 	line = get_next_line(0);
// 	while (line)
// 	{
// 		if (ft_strncmp(line, shell->cmds->redirections->file, len) == 0 || line[len] == '\0')
// 			break ;
// 		write(shell->wread[1], line, ft_strlen(line));
// 		free(line);
// 		line = get_next_line(0);
// 	}
// 	free(line);
// 	close(shell->wread[1]);
// 	free(shell->pids);
// 	close(0);
// 	get_next_line(0);
// 	exit(0);
// }

int	here_doc_input(t_shell *shell)
{

	if (pipe(shell->wread) == -1)
		exit(1);
	shell->hereid = fork();
	if (shell->hereid == -1)
		exit(1);
	if (shell->hereid == 0)
		here_doc_read(shell, shell->wread);
	close(shell->wread[1]);
	if (shell->cmds->redirections->next)
		shell->cmds->redirections = shell->cmds->redirections->next;
	return (shell->wread[0]);
}

// void	child_start(t_shell *shell, int *shell->wread)
// {
// 	int	fd;

// 	fd = open(shell->infile, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		close(shell->wread[0]);
// 		close(shell->wread[1]);
// 		close(fd);
// 		perror(shell->infile);
// 		exit(1);
// 	}
// 	close(shell->wread[0]);
// 	dup2(fd, 0);
// 	close(fd);
// 	dup2(shell->wread[1], 1);
// 	close(shell->wread[1]);
// 	exec_cmd(shell->cmds->cmd_args, shell->env);
// }

// void	child_process(t_shell *shell, int i, int prev_fd, int *shell->wread)
// {
// 	(void)i;
// 	dup2(prev_fd, 0);
// 	close(prev_fd);
// 	dup2(shell->wread[1], 1);
// 	close(shell->wread[1]);
// 	close(shell->wread[0]);
// 	exec_cmd(shell->cmds->cmd_args, shell->env);
// }

// void	child_end(t_shell *shell, int prev_fd)
// {
// 	int	fd;
// 	int	flags;

// 	flags = O_WRONLY | O_CREAT | O_TRUNC;
// 	if (shell->limiter)
// 		flags = O_WRONLY | O_CREAT | O_APPEND;
// 	fd = open(shell->outfile, flags, 0644);
// 	if (fd == -1)
// 	{
// 		close(prev_fd);
// 		close(fd);
// 		perror(shell->outfile);
// 		exit(1);
// 	}
// 	dup2(prev_fd, 0);
// 	close(prev_fd);
// 	dup2(fd, 1);
// 	close(fd);
// 	exec_cmd(shell->cmds->cmd_args, shell->env);
// }
