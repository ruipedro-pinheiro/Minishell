/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:37:10 by saouissi          #+#    #+#             */
/*   Updated: 2026/07/08 19:12:04 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			&& (env[indx][ft_strlen(name)] == '='
			|| env[indx][ft_strlen(name)] == '\0'))
			return (indx);
		indx++;
	}
	return (-1);
}
