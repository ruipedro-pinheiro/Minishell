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
	int		start;
	char	*value;
	char	quote_char;

	start = *i;
	quote_char = 0;
	while (line[*i] && (quote_char || (line[*i] != ' ' && line[*i] != '\t'
				&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')))
	{
		if (quote_char == 0 && (line[*i] == '\'' || line[*i] == '"'))
			quote_char = line[*i];
		else if (quote_char != 0 && line[*i] == quote_char)
			quote_char = 0;
		(*i)++;
	}
	value = ft_substr(line, start, *i - start);
	add_token(head, last, new_token(TOKEN_WORD, value));
	free(value);
}

t_token	*lexer(char *line, t_shell *shell)
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
		if (ft_strnstr(line, "exit", ft_strlen(line)))
			exiter(shell);
		if (!line[i])
			break ;
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			handle_operator(line, &i, &head, &last);
		else
			handle_word(line, &i, &head, &last);
	}
	return (head);
}
