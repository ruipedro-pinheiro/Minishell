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

	tmp = tokens;
	while (tokens)
	{
		tokens->value = NULL;
		free(tokens->value);
		if (tokens->next)
		{
			tmp = tokens->next;
			tokens->next = NULL;
		}
		free(tokens->next);
		tokens = tmp;
	}
	free(tokens);
}

t_cmd	*build_cmds(t_token *tokens)
{
	(void )tokens;
	return (NULL);
}

t_cmd	*parse(char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;
	tokens = lexer(&tokens, line);
	cmds = build_cmds(tokens);
	free_tokens(tokens);
	return (cmds);
}
