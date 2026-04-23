/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:15:45 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/21 22:01:08 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next_cmd;
	t_redir	*redir;
	t_redir	*next_redir;
	int		i;

	while (cmds)
	{
		next_cmd = cmds->next;
		i = 0;
		while (cmds->cmd_args && cmds->cmd_args[i])
			free(cmds->cmd_args[i++]);
		free(cmds->cmd_args);
		redir = cmds->redirections;
		while (redir)
		{
			next_redir = redir->next;
			free(redir->file);
			free(redir);
			redir = next_redir;
		}
		free(cmds);
		cmds = next_cmd;
	}
}

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
	if (!cmd)
		return (NULL);
	cmd->next = NULL;
	cmd->redirections = NULL;
	cmd->cmd_args = malloc(sizeof(char *) * (count_args(*tokens) + 1));
	if (!cmd->cmd_args)
		return (free(cmd), NULL);
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
			cmd->cmd_args[i++] = ft_strdup((*tokens)->value);
		else if (is_redir(*tokens) && (*tokens)->next)
		{
			append_redir(&cmd->redirections,
				token_to_redir_type((*tokens)->type), (*tokens)->next->value);
			*tokens = (*tokens)->next;
		}
		*tokens = (*tokens)->next;
	}
	return (cmd->cmd_args[i] = NULL, cmd);
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
			tail = new_cmd;
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

t_cmd	*parse(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(line, shell);
	debug_tokens(tokens, line);
	cmds = build_cmds(tokens);
	free_tokens(tokens);
	return (cmds);
}
