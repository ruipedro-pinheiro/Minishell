/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:11:38 by saouissi          #+#    #+#             */
/*   Updated: 2026/06/16 19:28:48 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	shredder(char *a)
{
	int x;

	x = ft_strlen(a);
	while (a[x] != '/')
		x--;
	a = ft_substr(a, 0, x);
}

static int	nbe(char *name, t_shell *shell)
{
	char	**env;
	int		i;

	i = 0;
	env = shell->env;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			if (env[i][ft_strlen(name)] == '=')
				return (i);
		}
		i++;
	}
	return (0);
}

char	*dotter(t_shell *shell, char *b)
{
	char	**split;
	char	*a;
	int	x;

	x = 0;
	if (b[0] == '/')
		a = ft_strdup("/");
	else if (b[0] == '~')
		a = ft_strdup(variable_expansion("HOME", shell));
	else
		a = ft_strdup(variable_expansion("PWD", shell));
	split = ft_split(b, '/');
	while (split[x])
	{
		
		if (ft_strncmp(split[x], ".", 2) == 0 && ft_strlen(split[x]) == 1)
			x++;
		else
		{
			if (ft_strncmp(split[x], "..", 3) == 0)
				shredder(a);
			else
			{
				a = ft_strjoin_char(a, '/');
				a = ft_strjoin(a, split[x]);
			}
			x++;
		}
	}
	printf("%s", a);
	return (a);
}

void	cder(t_shell *shell)
{
	int	x;
	int	y;

	x = nbe("OLDPWD", shell);
	y = nbe("PWD", shell);
	if (!shell->cmds->cmd_args[1])
	{
		// free(shell->env[x]);
		shell->env[x] = ft_strjoin("OLDPWD=", variable_expansion("PWD", shell));
		// free(shell->env[y]);
		shell->env[y] = ft_strjoin("PWD=", variable_expansion("HOME", shell));
		write(1, "ooo", 3);
		return ;
	}
	// dotter(shell, shell->cmds->cmd_args[1]);
}

