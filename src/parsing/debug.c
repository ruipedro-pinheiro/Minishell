/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 21:50:50 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/21 22:15:00 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*token_name(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_PIPE)
		return ("PIPE");
	if (type == TOKEN_REDIR_IN)
		return ("REDIR_IN");
	if (type == TOKEN_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == TOKEN_REDIR_APPEND)
		return ("REDIR_APPEND");
	if (type == TOKEN_REDIR_HEREDOC)
		return ("REDIR_HEREDOC");
	return ("UNKNOWN");
}

static char	*redir_name(t_redir_type type)
{
	if (type == REDIR_IN)
		return ("<");
	if (type == REDIR_OUT)
		return (">");
	if (type == REDIR_APPEND)
		return (">>");
	if (type == REDIR_HEREDOC)
		return ("<<");
	return ("?");
}

void	debug_tokens(t_token *tokens, char *line)
{
	int	fd;
	int	i;

	fd = open("debug.log", O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return ;
	ft_putstr_fd("=== PROMPT ===\n", fd);
	ft_putendl_fd(line, fd);
	ft_putstr_fd("\n=== TOKENS ===\n", fd);
	i = 0;
	while (tokens)
	{
		ft_putstr_fd("[", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd("] ", fd);
		ft_putstr_fd(token_name(tokens->type), fd);
		ft_putstr_fd("(", fd);
		if (tokens->value)
			ft_putstr_fd(tokens->value, fd);
		else
			ft_putstr_fd("null", fd);
		ft_putstr_fd(")\n", fd);
		tokens = tokens->next;
		i++;
	}
	close(fd);
}

static void	debug_one_cmd(t_cmd *cmd, int cmd_i, int fd)
{
	int		i;
	t_redir	*redir;

	ft_putstr_fd("cmd[", fd);
	ft_putnbr_fd(cmd_i, fd);
	ft_putstr_fd("]\n  argv:", fd);
	i = 0;
	while (cmd->cmd_args && cmd->cmd_args[i])
	{
		ft_putstr_fd(" [", fd);
		ft_putstr_fd(cmd->cmd_args[i], fd);
		ft_putstr_fd("]", fd);
		i++;
	}
	if (i == 0)
		ft_putstr_fd(" none", fd);
	ft_putstr_fd("\n  redirs:", fd);
	redir = cmd->redirections;
	while (redir)
	{
		ft_putstr_fd(" ", fd);
		ft_putstr_fd(redir_name(redir->type), fd);
		ft_putstr_fd(" ", fd);
		ft_putstr_fd("[", fd);
		if (redir->file)
			ft_putstr_fd(redir->file, fd);
		else
			ft_putstr_fd("null", fd);
		ft_putstr_fd("]", fd);
		redir = redir->next;
	}
	if (!cmd->redirections)
		ft_putstr_fd(" none", fd);
	ft_putstr_fd("\n  next: ", fd);
	if (cmd->next)
		ft_putstr_fd("YES\n", fd);
	else
		ft_putstr_fd("NULL\n", fd);
}

void	debug_cmds(t_cmd *cmds)
{
	int	fd;
	int	i;

	fd = open("debug.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	ft_putstr_fd("=== CMDS ===\n", fd);
	i = 0;
	while (cmds)
	{
		debug_one_cmd(cmds, i, fd);
		cmds = cmds->next;
		i++;
	}
	ft_putstr_fd("------------------\n", fd);
	close(fd);
}
