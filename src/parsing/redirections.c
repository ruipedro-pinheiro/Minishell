/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:25:56 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/17 16:41:11 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir_type	set_redir_type(t_token *tokens)
{
	t_redir	*redir;

	redir = (t_redir *)0 ;
	if (tokens->type == TOKEN_REDIR_APPEND)
		redir->type = REDIR_APPEND;
	else if (tokens->type == TOKEN_REDIR_HEREDOC)
		redir->type = REDIR_HEREDOC;
	else if (tokens->type == TOKEN_REDIR_IN)
		redir->type = REDIR_IN;
	else if (tokens->type == TOKEN_REDIR_OUT)
		redir->type = REDIR_OUT;
	return (redir->type);
}

t_redir	*build_redirs(t_token *tokens)
{
	t_redir	*head;
	t_redir *node;

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
