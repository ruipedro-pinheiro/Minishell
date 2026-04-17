/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:29:13 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/15 18:05:19 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_in_redirs(char *line, int *i, t_token **head, t_token **last)
{
	if (line[*i + 1] == '<')
	{
		add_token(head, last, new_token(TOKEN_REDIR_HEREDOC, "<<"));
		*i += 2;
	}
	else
	{
		add_token(head, last, new_token(TOKEN_REDIR_IN, "<"));
		(*i)++;
	}
}

void	handle_out_redirs(char *line, int *i, t_token **head, t_token **last)
{
	if (line[*i + 1] == '>')
	{
		add_token(head, last, new_token(TOKEN_REDIR_APPEND, ">>"));
		*i += 2;
	}
	else
	{
		add_token(head, last, new_token(TOKEN_REDIR_OUT, ">"));
		(*i)++;
	}
}

void	handle_operator(char *line, int *i, t_token **head, t_token **last)
{
	if (line[*i] == '|')
	{
		add_token(head, last, new_token(TOKEN_PIPE, "|"));
		(*i)++;
	}
	else if (line[*i] == '<')
	{
		handle_in_redirs(line, i, head, last);
	}
	else if (line[*i] == '>')
	{
		handle_out_redirs(line, i, head, last);
	}
}

void	handle_word(char *line, int *i, t_token **head, t_token **last)
{
	(void)i;
	(void)line;
	(void)*head;
	(void)*last;
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
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			handle_operator(line, &i, &head, &last);
		else
			handle_word(line, &i, &head, &last);
	}
	return (head);
}
