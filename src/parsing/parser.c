/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:15:45 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/21 18:17:23 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_args(t_token *tokens)
{
	int		n_args;

	n_args = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (is_redir(tokens))
		{
			tokens = tokens->next;
			if (tokens)
				tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_WORD)
		{
			n_args++;
			tokens = tokens->next;
		}
	}
	return (n_args);
}

t_cmd	*build_one_cmd(t_token **tokens)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	cmd->cmd_args = malloc(sizeof(char *) * (count_args(*tokens) + 1));
	cmd->next = NULL;
	cmd->redirections = NULL;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			cmd->cmd_args[i++] = ft_strdup((*tokens)->value);
		}
		else if (is_redir(*tokens) && (*tokens)->next)
		{
			append_redir(&cmd->redirections,
				token_to_redir_type((*tokens)->type), (*tokens)->next->value);
		}
		*tokens = (*tokens)->next;
	}
	cmd->cmd_args[i] = NULL;
	return (cmd);
}

t_cmd	*build_cmds(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*new_cmd;

	head = NULL;
	tail = NULL;
	while (tokens)
	{
		new_cmd = build_one_cmd(&tokens);
		if (!new_cmd)
			return (head);
		if (!head)
		{
			head = new_cmd;
		}
		else
		{
			tail->next = new_cmd;
			tail = new_cmd;
		}
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (head);
}

t_cmd	*parse(char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(line);
	cmds = build_cmds(tokens);
	free_tokens(tokens);
	return (cmds);
}
