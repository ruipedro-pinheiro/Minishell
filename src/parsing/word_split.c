/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:00:00 by rpinheir          #+#    #+#             */
/*   Updated: 2026/05/28 12:00:00 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mark_range(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == ' ' || s[i] == '\t')
			s[i] = WS_SEP;
}

int	count_fields(char *value)
{
	char	**fields;
	int		k;

	fields = ft_split(value, WS_SEP);
	if (!fields)
		return (0);
	k = 0;
	while (fields[k])
		free(fields[k++]);
	return (free(fields), k);
}

void	fill_fields(char *value, char **cmd_args, int *i)
{
	char	**fields;
	int		k;

	k = -1;
	fields = ft_split(value, WS_SEP);
	if (!fields)
		return ;
	while (fields[++k])
		cmd_args[(*i)++] = fields[k];
	free(fields);
}
