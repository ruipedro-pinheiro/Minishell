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

static void	here_doc_read(t_pipex *pipex, int *pipe_fd)
{
	char	*line;
	int		len;

	close(pipe_fd[0]);
	len = ft_strlen(pipex->limiter);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, pipex->limiter, len) == 0 || line[len] == '\0')
			break ;
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(pipe_fd[1]);
	free(pipex->pids);
	close(0);
	get_next_line(0);
	exit(0);
}

int	here_doc_input(t_pipex *pipex)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		here_doc_read(pipex, pipe_fd);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	child_start(t_pipex *pipex, int *pipe_fd)
{
	int	fd;

	fd = open(pipex->infile, O_RDONLY);
	if (fd == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(fd);
		perror(pipex->infile);
		exit(1);
	}
	close(pipe_fd[0]);
	dup2(fd, 0);
	close(fd);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	exec_cmd(pipex->cmds[0], pipex->envp);
}

void	child_process(t_pipex *pipex, int i, int prev_fd, int *pipe_fd)
{
	dup2(prev_fd, 0);
	close(prev_fd);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	exec_cmd(pipex->cmds[i], pipex->envp);
}

void	child_end(t_pipex *pipex, int prev_fd)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (pipex->limiter)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(pipex->outfile, flags, 0644);
	if (fd == -1)
	{
		close(prev_fd);
		close(fd);
		perror(pipex->outfile);
		exit(1);
	}
	dup2(prev_fd, 0);
	close(prev_fd);
	dup2(fd, 1);
	close(fd);
	exec_cmd(pipex->cmds[pipex->cmd_count - 1], pipex->envp);
}
