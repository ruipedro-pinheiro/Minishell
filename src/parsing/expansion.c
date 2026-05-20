/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:58:04 by rpinheir          #+#    #+#             */
/*   Updated: 2026/05/13 16:44:43 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	["hello"]			-> hello				OK
	['hello']			-> hello				OK
	['hello "there"']	-> hello "there"		OK
	["hello 'there'"]	-> hello 'there'		OK
	['hello $USER']		-> hello $USER			OK
	["hello $USER"]		-> hello rpinheir		OK
	["hello '$USER'"]	-> hello 'rpinheir'		OK
	['hello "$USER"']	-> hello "$USER"		OK
*/

char	*variable_expansion(char *name, t_shell *shell)
{
	char	**env;
	int		i;

	i = -1;
	env = shell->env;
	while (env[++i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			if (env[i][ft_strlen(name)] == '=')
			{
				name = &env[i][ft_strlen(name) + 1];
				return (name);
			}
		}
	}
	return ("");
}

char	*exit_status_handler(int *i, char *new_value, t_shell *shell)
{
	char	*tmp;
	char	*exit;

	exit = ft_itoa(shell->exit_status);
	tmp = ft_strjoin(new_value, exit);
	free(new_value);
	free(exit);
	*i = *i + 1;
	return (tmp);
}

char	*dollar_handler(char *new_value, char *value, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	int		length;
	char	*tmp;

	length = 0;
	if (value[*i + 1] == '?')
		return (exit_status_handler(i, new_value, shell));
	while (ft_isalnum(value[*i + 1 + length]) || value[*i + 1 + length] == '_')
		length++;
	if (length == 0)
	{
		tmp = ft_strjoin(new_value, "$");
		free(new_value);
		new_value = tmp;
		return (new_value);
	}
	var_name = ft_substr(value, *i + 1, length);
	var_value = variable_expansion(var_name, shell);
	tmp = ft_strjoin(new_value, var_value);
	free(new_value);
	free(var_name);
	new_value = tmp;
	return (*i = *i + length, new_value);
}

char	*token_expand(char *value, t_shell *shell, bool	*is_var)
{
	char	*new_value;
	bool	is_dquote;
	bool	is_squote;
	int		i;

	new_value = ft_strdup("");
	is_squote = false;
	is_dquote = false;
	i = -1;
	while (value[++i])
	{
		if (value[i] == '\'' && !is_dquote)
			is_squote = !is_squote;
		else if (value[i] == '"' && !is_squote)
			is_dquote = !is_dquote;
		else if (value[i] == '$' && !is_squote)
		{
			*is_var = true;
			new_value = dollar_handler(new_value, value, &i, shell);
		}
		else
			new_value = ft_strjoin_char(new_value, value[i]);
	}
	return (new_value);
}

bool	expansion(t_token *head, t_shell *shell)
{
	t_token	*node;
	char	*value;

	if (!head)
		return (false);
	node = head;
	while (node)
	{
		if (node->type == TOKEN_WORD)
		{
			node->is_var = false;
			value = token_expand(node->value, shell, &node->is_var);
			free(node->value);
			node->value = value;
		}
		node = node->next;
	}
	return (true);
}
