/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:41:33 by saouissi          #+#    #+#             */
/*   Updated: 2026/07/03 17:42:45 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_name_valid(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (false);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

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