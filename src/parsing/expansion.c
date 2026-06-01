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

char	*value_extraction(char *name, t_shell *shell)
{
	char	**new_value;
	int		i;

	i = -1;
	new_value = shell->env;
	while (new_value[++i])
	{
		if (ft_strncmp(new_value[i], name, ft_strlen(name)) == 0)
		{
			if (new_value[i][ft_strlen(name)] == '=')
			{
				name = &new_value[i][ft_strlen(name) + 1];
				return (name);
			}
		}
	}
	return ("");
}

char	*value_expand(char *value, int *i, t_shell *shell)
{
	char	*name;
	char	*val;
	int		len;

	if (value[*i + 1] == '?')
		return (*i += 1, ft_itoa(shell->exit_status));
	len = 0;
	while (ft_isalnum(value[*i + 1 + len]) || value[*i + 1 + len] == '_')
		len++;
	if (len == 0)
		return (ft_strdup("$"));
	name = ft_substr(value, *i + 1, len);
	val = ft_strdup(value_extraction(name, shell));
	free(name);
	*i += len;
	return (val);
}

char	*join_expand(char *new_value, char *value, bool is_dq, bool *is_var)
{
	char	*res;

	*is_var = true;
	if (!is_dq)
		mark_range(value);
	res = ft_strjoin(new_value, value);
	free(new_value);
	free(value);
	return (res);
}

char	*token_expand(char *value, t_shell *shell, bool	*is_var)
{
	char	*new_value;
	bool	is_dq;
	bool	is_sq;
	int		i;

	new_value = ft_strdup("");
	is_sq = false;
	is_dq = false;
	i = -1;
	while (value[++i])
	{
		if (value[i] == '\'' && !is_dq)
			is_sq = !is_sq;
		else if (value[i] == '"' && !is_sq)
			is_dq = !is_dq;
		else if (value[i] == '$' && !is_sq)
			new_value = join_expand(new_value, value_expand(value, &i, shell),
					is_dq, is_var);
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
