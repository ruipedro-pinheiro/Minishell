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
	return (-1);
}

static int	verif(t_shell *shell)
{
	char	*path;

	path = dotter(shell, shell->cmds->cmd_args[1]);
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(shell->cmds->cmd_args[1], 2);
		free(path);
		shell->exit_status = 1;
		return (1);
	}
	if (access(path, X_OK) != 0)
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putendl_fd(shell->cmds->cmd_args[1], 2);
		free(path);
		shell->exit_status = 1;
		return (1);
	}
	free(path);
	return (0);
}

static void	earlier(int x, int y, t_shell *shell, int mode)
{
	char	*a;
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", variable_expansion("PWD", shell));
	if (mode == 1)
	{
		a = variable_expansion("HOME", shell);
		chdir(a);
		free(shell->env[x]);
		shell->env[x] = tmp;
		free(shell->env[y]);
		shell->env[y] = ft_strjoin("PWD=", a);
	}
	if (mode == 2)
	{
		a = ft_strdup(variable_expansion("OLDPWD", shell));
		chdir(a);
		free(shell->env[x]);
		shell->env[x] = tmp;
		free(shell->env[y]);
		shell->env[y] = ft_strjoin("PWD=", a);
		free(a);
	}
}

void	cder(t_shell *shell)
{
	int		x;
	int		y;
	char	*path;
	char	*tmp;

	x = nbe("OLDPWD", shell);
	y = nbe("PWD", shell);
	if (x == -1 || y == -1)
		return ;
	shell->exit_status = 0;
	if (!shell->cmds->cmd_args[1])
		return (earlier(x, y, shell, 1));
	if (shell->cmds->cmd_args[1][0] == '-')
		return (earlier(x, y, shell, 2));
	if (verif(shell) == 1)
		return ;
	path = dotter(shell, shell->cmds->cmd_args[1]);
	tmp = ft_strjoin("OLDPWD=", variable_expansion("PWD", shell));
	free(shell->env[x]);
	shell->env[x] = tmp;
	chdir(path);
	free(shell->env[y]);
	shell->env[y] = ft_strjoin("PWD=", path);
	free(path);
}
