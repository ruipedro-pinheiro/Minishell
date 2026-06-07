/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:11:38 by saouissi          #+#    #+#             */
/*   Updated: 2026/06/07 19:20:23 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	nbe(char *name, t_shell *shell)
{
	char	**env;
	int		i;

	i = -1;
	env = shell->env;
	while (env[++i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
			return (i);
	}
	return (0);
}

static void	dotter(t_shell *shell)
{
	char	**splitdir;
	char	*a;
	int	x;

	x = 0;
	if (shell->cmds->cmd_args[0] == '/')
		a = ft_strdup("/");
	else if (shell->cmds->cmd_args[0] == '~')
		a = ft_strdup(shell->env[nbe("HOME", shell)]);
	else
		a = ft_strdup(shell->env[nbe("PWD", shell)]);
	splitdir = ft_split(shell->cmds->cmd_args, '/');
	while (splitdir[x])
	{
		
	}
}

void	cder(t_shell *shell)
{
	int	x;
	int	y;

	x = nbe("OLDPWD", shell);
	y = nbe("PWD", shell);
	if (!shell->cmds->next)
	{
		free(shell->env[x]);
		shell->env[x] = ft_strjoin(ft_strdup("OLDPWD="), variable_expansion("PWD", shell));
		free(shell->env[y]);
		shell->env[y] = ft_strjoin(ft_strdup("PWD="), variable_expansion("HOME", shell));
		return ;
	}
	shell->cmds = shell->cmds->next;
	dotter(shell);
}

