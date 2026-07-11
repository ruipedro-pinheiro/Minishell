/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:11:38 by saouissi          #+#    #+#             */
/*   Updated: 2026/07/11 18:43:00 by saouissi         ###   ########.fr       */
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

static int	verif(t_shell *shell)
{
	if (access(dotter(shell, shell->cmds->cmd_args[1]), F_OK) != 0)
	{
		printf("cd: no such file or directory: %s\n", shell->cmds->cmd_args[1]);
		return (1);
	}
	if (access(dotter(shell, shell->cmds->cmd_args[1]), X_OK) != 0)
	{
		printf("cd: permission denied: %s\n", shell->cmds->cmd_args[1]);
		return (1);
	}
	return (0);
}

static void	earlier(int x, int y, t_shell *shell, int mode)
{
	char	*a;

	if (mode == 1)
	{
		// free(shell->env[x]);
		shell->env[x] = ft_strjoin("OLDPWD=", variable_expansion("PWD", shell));
		// free(shell->env[y]);
		chdir(variable_expansion("HOME", shell));
		shell->env[y] = ft_strjoin("PWD=", variable_expansion("HOME", shell));
		return ;
	}
	if (mode == 2)
	{
		a = variable_expansion("OLDPWD", shell);
		shell->env[x] = ft_strjoin("OLDPWD=", variable_expansion("PWD", shell));
		chdir(a);
		shell->env[y] = ft_strjoin("PWD=", a);
		return ;
	}
}

void	cder(t_shell *shell)
{
	int		x;
	int		y;

	x = nbe("OLDPWD", shell);
	y = nbe("PWD", shell);
	if (!shell->cmds->cmd_args[1])
		return (earlier(x, y, shell, 1));
	if (shell->cmds->cmd_args[1] && shell->cmds->cmd_args[1][0] == '-')
		return (earlier(x, y, shell, 2));
	if (verif(shell) == 1)
		return ;
	shell->env[x] = ft_strjoin("OLDPWD=", variable_expansion("PWD", shell));
	chdir(dotter(shell, shell->cmds->cmd_args[1]));
	shell->env[y] = ft_strjoin("PWD=", dotter(shell, shell->cmds->cmd_args[1]));
}
