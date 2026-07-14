/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro </var/spool/mail/pedro>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:13:21 by pedro             #+#    #+#             */
/*   Updated: 2026/06/29 11:14:39 by pedro            ###   ########.ch       */
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
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i + 1])) > 0)
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
