/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro </var/spool/mail/pedro>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 11:41:29 by pedro             #+#    #+#             */
/*   Updated: 2026/07/17 17:29:41 by pedro            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*heredoc_expand(t_shell *shell)
{
	char	*res;
	int		i;
	char	*line;
	char	*val;

	line = get_next_line(0);
	if (!line)
		return (NULL);
	res = ft_strdup("");
	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			val = value_expand(line, &i, shell);
			res = ft_strapnd(res, val);
			free(val);
		}
		else
			res = ft_strjoin_char(res, line[i]);
	}
	free(line);
	return (res);
}

static char	*detect_null_eof(t_shell *shell, t_redir *redir)
{
	char	*line;

	write(1, HD_MARK, ft_strlen(HD_MARK));
	if (redir->is_quoted)
		line = get_next_line(0);
	else
		line = heredoc_expand(shell);
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document delimited by "
			"end-of-file (wanted `", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putendl_fd("')", 2);
	}
	return (line);
}

void	here_doc_read(t_shell *shell, t_redir *redir)
{
	char	*line;
	int		limsize;

	line = "";
	close(shell->wread[0]);
	limsize = ft_strlen(redir->file);
	while (line)
	{
		line = detect_null_eof(shell, redir);
		if (!line)
			break ;
		if (ft_strncmp(line, redir->file, limsize) == 0
			&& ft_strlen(line) == limsize + 1
			&& line[ft_strlen(line) - 1] == '\n')
			break ;
		write(shell->wread[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(shell->wread[1]);
	close(0);
	exit(0);
}

int	here_doc_input(t_shell *shell, t_redir *redir)
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
		signal(SIGQUIT, SIG_IGN);
		here_doc_read(shell, redir);
	}
	waitpid(shell->hereid, &status, 0);
	close(shell->wread[1]);
	if (WIFSIGNALED(status))
	{
		shell->exit_status = EXIT_SIGNAL_BASE + WTERMSIG(status);
		return (-2);
	}
	else
		shell->exit_status = WEXITSTATUS(status);
	return (shell->wread[0]);
}
