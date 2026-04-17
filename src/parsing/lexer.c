/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:29:13 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/17 16:52:48 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_word(char *line, int *i, t_token **head, t_token **last)
{
	bool	is_in_quote;
	char	*buffer;

	is_in_quote = false;
	buffer = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!buffer)
	{
		(*i)++;
		return ;
	}
	while (line[*i])
	{
		if (line[*i] == 34 || line[*i] == 39)
			is_in_quote = !is_in_quote;
		if (is_in_quote)
			buffer[*i] = line[*i];
		(*i)++;
		add_token(head, last, new_token(TOKEN_WORD, "A"));
		(void)*head;
		(void)*last;
	}
}

t_token	*lexer(char *line)
{
	int		i;
	t_token	*head;
	t_token	*last;

	head = NULL;
	last = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!line[i])
			break;
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			handle_operator(line, &i, &head, &last);
		else
			handle_word(line, &i, &head, &last);
	}
	return (head);
}
