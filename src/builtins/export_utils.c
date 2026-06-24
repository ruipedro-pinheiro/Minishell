/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:18:31 by rpinheir          #+#    #+#             */
/*   Updated: 2026/06/24 12:04:38 by pedro            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	display_export(char **env)
{
	int		i;
	char	*eq;

	i = 0;
	while (env[i])
	{
		eq = ft_strchr(env[i], '=');
		ft_putstr_fd("declare -x ", 1);
		if (!eq)
			ft_putendl_fd(env[i], 1);
		else
		{
			write(1, env[i], eq - env[i] + 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(eq + 1, 1);
			ft_putendl_fd("\"", 1);
		}
		i++;
	}
}

void	sort_env(char **env)
{
	int		i;
	char	*tmp;
	bool	swapped;

	swapped = true;
	while (swapped)
	{
		swapped = false;
		i = 0;
		while (env[i + 1])
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i] + 1)) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				swapped = true;
			}
			i++;
		}
	}
	display_export(env);
}

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
	return (-1);
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
