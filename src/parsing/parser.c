/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:15:45 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/15 17:48:50 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens);
		tokens = tmp;
	}
}

bool	is_redir(t_token *tokens)
{
	if (tokens->type == TOKEN_REDIR_APPEND
		|| tokens->type == TOKEN_REDIR_HEREDOC || tokens->type == TOKEN_REDIR_IN
		|| tokens->type == TOKEN_REDIR_OUT)
		return (true);
	return (false);
}

int	count_args(t_token *tokens)
{
	int n;

	n = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			n++;
		tokens = tokens->next;
	}
	return (n);
}

t_cmd	*build_cmds(t_token *tokens)
{
	t_cmd	*cmds;
	int		i;
	int		n;

	i = 0;
	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	n = count_args(tokens);
	cmds->cmd_args = malloc(sizeof(char *) * (n + 1));
	if (!cmds->cmd_args)
		return (NULL);
	cmds->redirections = NULL;
	cmds->next = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			cmds->cmd_args[i++] = ft_strdup(tokens->value);
		tokens = tokens->next;
	}
	cmds->cmd_args[i] = NULL;
	return (cmds);
}

t_cmd	*parse(char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(line);
	cmds = build_cmds(tokens);
	free_tokens(tokens);
	return (cmds);
}
