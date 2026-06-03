/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:40:55 by rpinheir          #+#    #+#             */
/*   Updated: 2026/06/03 19:27:57 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exporter(t_shell *shell, char *name, char *value)
{
	int	i;
	int j;
	int	k;
	int end;

	end = -1;
	j = 0;
	i = 0;
	k = 0;
	while(shell->env[++end])
		;
	while(shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0)
		{
			if (shell->env[i][j+1] == '=')
			{
				j+=2;
				shell->env[i][j] = value[k];
			}
		}
		shell->env[end] = ft_strjoin(name, "=");
		shell->env[end] = ft_strjoin(shell->env[end], value);
		i++;
	}
}
