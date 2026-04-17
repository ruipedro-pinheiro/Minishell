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

t_cmd	*build_cmds(t_token *tokens)
{
	(void )tokens; // placeholder so compilation works
	return (NULL);
}

t_cmd *parse(char *line)
{
    t_token *tokens;
	t_cmd   *cmds;

	tokens = lexer(line);
    cmds = build_cmds(tokens);
    //free tokens;
    return (cmds); // returning start of linked list;
}
