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
