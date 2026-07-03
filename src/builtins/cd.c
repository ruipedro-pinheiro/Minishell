/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:11:38 by saouissi          #+#    #+#             */
/*   Updated: 2026/07/03 18:20:16 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	cder(t_shell *shell)
{
	int	x;
	int	y;
	char	*a;

	x = nbe("OLDPWD", shell);
	y = nbe("PWD", shell);
	if (!shell->cmds->cmd_args[1])
	{
		shell->env[x] = ft_strjoin("OLDPWD=", variable_expansion("PWD", shell));
		shell->env[y] = ft_strjoin("PWD=", variable_expansion("HOME", shell));
		return ;
	}
	if (shell->cmds->cmd_args[1] && shell->cmds->cmd_args[1][0] == '-')
	{
		a = variable_expansion("OLDPWD", shell);
		shell->env[x] = ft_strjoin("OLDPWD=", variable_expansion("PWD", shell));
		shell->env[y] = ft_strjoin("PWD=", a);
		return ;
	}
	if (access(dotter(shell, shell->cmds->cmd_args[1]), F_OK) != 0)
	{
		printf("file nonexistent\n");
		return ;
	}
	if (access(dotter(shell, shell->cmds->cmd_args[1]), X_OK) != 0)
	{
		printf("no perms\n");
		return ;
	}
	shell->env[x] = ft_strjoin("OLDPWD=", variable_expansion("PWD", shell));
	shell->env[y] = ft_strjoin("PWD=", dotter(shell, shell->cmds->cmd_args[1]));
}

