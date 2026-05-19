/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:15:45 by rpinheir          #+#    #+#             */
/*   Updated: 2026/05/17 13:45:00 by pedro            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*parse(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(line);
	if (!tokens)
		return (NULL);
	debug_tokens(tokens, line);
	if (!validation(tokens))
		return (free_tokens(tokens), NULL);
	if (!expansion(tokens, shell))
		return (free_tokens(tokens), NULL);
	cmds = build_cmds(tokens);
	free_tokens(tokens);
	return (cmds);
}
