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
		|| tokens->type == TOKEN_REDIR_OUT || tokens->type == TOKEN_PIPE)
		return (true);
	return (false);
}

t_cmd	*build_cmds(t_token *tokens)
{
	t_cmd *cmds;
	int	i;

	i = 0;
	cmds = malloc(sizeof(t_cmd));
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			cmds->cmd_args[i] = tokens->value;
			if (is_redir(tokens->next))
				cmds->redirections = build_redirs(tokens);
			i++;
		}
		tokens = tokens->next;
	}
	return (NULL);
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
