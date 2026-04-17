/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:38:48 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/17 16:47:11 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(t_token_type token_type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = token_type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token **last, t_token *token)
{
	if (!token)
	{
		token = new_token(token->type, token->value);
		if (!token)
			return ;
	}
	if (!*head)
	{
		*head = token;
		*last = token;
	}
	else
	{
		(*last)->next = token;
		*last = token;
	}
}
