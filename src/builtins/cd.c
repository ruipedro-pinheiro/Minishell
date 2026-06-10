/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:11:38 by saouissi          #+#    #+#             */
/*   Updated: 2026/06/10 18:51:14 by saouissi         ###   ########.fr       */
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

static void	dotter(t_shell *shell, int z, int z2)
{
	char	**splitdir;
	char	*a;
	int	x;

	x = 1;
	if (shell->cmds->cmd_args[1][0] == '/')
		a = ft_strdup("/");
	else if (shell->cmds->cmd_args[1][0] == '~')
		a = ft_strdup(shell->env[nbe("HOME", shell)]);
	else
		a = ft_strdup(shell->env[nbe("PWD", shell)]);
	splitdir = ft_split(shell->cmds->cmd_args[1], '/');
	while (splitdir[x])
	{
		if (ft_strncmp(splitdir[x], ".", 2) == 0)
			x++;
		else
		{
			if (ft_strncmp(splitdir[x], "..", 3) == 0)
				shredder(a);
			else
			{
				a = ft_strjoin_char(a, '/');
				a = ft_strjoin(a, splitdir[x]);
			}
			x++;
		}
	}
	free(shell->env[z]);
	shell->env[z] = ft_strjoin(ft_strdup("OLDPWD="), variable_expansion("PWD", shell));
	free(shell->env[z2]);
	shell->env[z2] = ft_strjoin(ft_strdup("PWD="), a);
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
	dotter(shell, x, y);
}

