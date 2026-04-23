/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:25:56 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/20 17:42:56 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir_type	set_redir_type(t_token *tokens)
{
	if (tokens->type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	else if (tokens->type == TOKEN_REDIR_HEREDOC)
		return (REDIR_HEREDOC);
	else if (tokens->type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	else if (tokens->type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	return ((t_redir_type)0);
}

t_redir	*build_redirs(t_token *tokens)
{
	t_redir	*head;
	t_redir	*node;

	head = malloc(sizeof(t_redir));
	if (!head)
		return (NULL);
	head->type = set_redir_type(tokens);
	while (tokens)
	{
		if (is_redir(tokens))
		{
			node = head;
			node->next = malloc(sizeof(t_redir));
			if (!node)
				return (NULL);
			head->type = set_redir_type(tokens);
			head->file = ft_strdup(tokens->next->value);
		}
		tokens = tokens->next;
	}
	return (head);
}

void	input_redirs(char *line, int *i, t_token **head, t_token **last)
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

void	output_redirs(char *line, int *i, t_token **head, t_token **last)
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
		input_redirs(line, i, head, last);
	}
	else if (line[*i] == '>')
	{
		output_redirs(line, i, head, last);
	}
}
