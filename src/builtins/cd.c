/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:11:38 by saouissi          #+#    #+#             */
/*   Updated: 2026/06/03 17:37:34 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	dotter(char *a, t_shell *shell)
{
	int	x;

	x = ft_strlen(a);
	if (a[1] == '.')
	{
		
	}
}

void	cder(t_shell *shell)
{
	char	*a;

	if (!shell->cmds->next)
	{
		free(shell->env[50]);
		shell->env[50] = ft_strdup(shell->env[20]);
		free(shell->env[20]);
		shell->env[20] = ft_strdup(shell->env[32]);
	}
	a = shell->cmds->next->cmd_args;
	if (a[0] == '.')
		dotter(a, shell);
	if (access(shell->cmds->next->cmd_args, X_OK) != 0)
	{
		printf("directory can not be accessed or does not exist\n");
		exit(-1);
	}
	free(shell->env[50]);
	shell->env[50] = ft_strdup(shell->env[20]);
	free(shell->env[20]);
}

