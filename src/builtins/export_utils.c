/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:18:31 by rpinheir          #+#    #+#             */
/*   Updated: 2026/06/10 14:24:42 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	find_env_var(char **env, char *name)
{
	int	indx;

	indx = 0;
	while (env[indx])
	{
		if (ft_strncmp(env[indx], name, ft_strlen(name)) == 0
			&& env[indx][ft_strlen(name)] == '=')
			return (indx);
		indx++;
	}
	return (0);
}

char	*get_value(char *arg)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	if (arg[i] == '\0')
		return (NULL);
	i++;
	j = i;
	while (arg[j])
		j++;
	value = malloc(sizeof(char) * (j - i) + 1);
	if (!value)
		return (NULL);
	j = 0;
	while (arg[i])
	{
		value[j] = arg[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

// TODO: bash: export: `=novarname': not a valid identifier
//		If there is no letters before = then there is no variable = error
char	*get_name(char *arg)
{
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	name = malloc(sizeof(char) * i + 1);
	if (!name)
		return (NULL);
	while (arg[j] != '=' && arg[j])
	{
		name[j] = arg[j];
		j++;
	}
	name[j] = '\0';
	return (name);
}
