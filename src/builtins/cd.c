/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:11:38 by saouissi          #+#    #+#             */
/*   Updated: 2026/06/18 18:50:58 by saouissi         ###   ########.fr       */
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

	x = nbe("OLDPWD", shell);
	y = nbe("PWD", shell);
	if (!shell->cmds->cmd_args[1])
	{
		// free(shell->env[x]);
		shell->env[x] = ft_strjoin("OLDPWD=", value_extraction("PWD", shell));
		// free(shell->env[y]);
		shell->env[y] = ft_strjoin("PWD=", value_extraction("HOME", shell));
		write(1, "ooo", 3);
		return ;
	}
	// dotter(shell, shell->cmds->cmd_args[1]);
}

