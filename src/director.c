/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   director.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 18:49:57 by saouissi          #+#    #+#             */
/*   Updated: 2026/07/08 19:09:17 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*shredder(char *a)
{
	int		x;
	char	*b;

	x = ft_strlen(a);
	while (a[x] != '/')
		x--;
	b = ft_substr(a, 0, x);
	return (b);
}

static char	*asetter(t_shell *shell, char b)
{
	if (b == '/')
		return (ft_strdup("/"));
	else if (b == '~')
		return (ft_strdup(variable_expansion("HOME", shell)));
	else
		return (ft_strdup(variable_expansion("PWD", shell)));
}

static int	xsetter(char b)
{
	if (b == '~')
		return (1);
	else
		return (0);
}

char	*dotter(t_shell *shell, char *b)
{
	char	**split;
	char	*a;
	int		x;

	a = asetter(shell, b[0]);
	x = xsetter(b[0]);
	split = ft_split(b, '/');
	while (split[x])
	{
		if (ft_strncmp(split[x], ".", 2) == 0 && ft_strlen(split[x]) == 1)
			x++;
		else
		{
			if (ft_strncmp(split[x], "..", 3) == 0)
				a = shredder(a);
			else
			{
				if (a[strlen(a) - 1] != '/')
					a = ft_strjoin_char(a, '/');
				a = ft_strjoin(a, split[x]);
			}
			x++;
		}
	}
	return (a);
}
