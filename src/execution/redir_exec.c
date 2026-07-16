/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro </var/spool/mail/pedro>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:21:52 by pedro             #+#    #+#             */
/*   Updated: 2026/07/15 19:42:45 by pedro            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_IN)
	{
		fd = open(redir->file, O_RDONLY, 0);
		return (fd);
	}
	else if (redir->type == REDIR_OUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return (fd);
	}
	else if (redir->type == REDIR_APPEND)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		return (fd);
	}
	return (-1);
}

int	apply_redirs(t_shell *shell)
{
	t_redir	*redir;
	int		fd;

	redir = shell->cmds->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			dup2(redir->heredoc_fd, STDIN_FILENO);
			redir = redir->next;
			continue ;
		}
		fd = open_redir(redir);
		if (fd == -1)
			return (-1);
		if (redir->type == REDIR_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (0);
}
