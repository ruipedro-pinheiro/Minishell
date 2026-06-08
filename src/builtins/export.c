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

static char *get_value(t_shell *shell)
{
	char *value;
	int	i;
	int	j;

	i = -1;
	j = 0;
	while(ft_strncmp(shell->cmds->cmd_args[i], "export", 7) == 0)
		i++;
	while(shell->cmds->cmd_args[i][j] != '=')
		j++;
	value = malloc(sizeof(char *) * j + 1);
	if (!value)
		return NULL;
	j++;
	while (shell->cmds->cmd_args[i][j])
	{
		value[j] = shell->cmds->cmd_args[i][j];
		j++;
	}
	value[j] = '\0';
	return (value);
}

static char	*get_name(t_shell *shell)
{
	char *name;
	int	i;
	int	j;

	i = -1;
	j = 0;
	while(ft_strncmp(shell->cmds->cmd_args[i], "export", 7) == 0)
		i++;
	while(shell->cmds->cmd_args[i][j] != '=')
		j++;
	name = malloc(sizeof(char *) * j);
	if (!name)
		return NULL;
	while (shell->cmds->cmd_args[i][j] != '=')
	{
		name[j] = shell->cmds->cmd_args[i][j];
		j++;
	}
	name[j] = '\0';
	return (name);
}
/*
	TODO: divide funtion into multiple functions
			1. Display of environment with declare -x
			2. Export value
			3. Parsing value and data from cmds

	TODO: Add variable (if not existing already)
			1. Count size of n
			2. Malloc new array of n + 2
			3. Copy pointers (no strdup)
			4. case n = name=value (ft_strjoin), case n+1 = NULL
			5. free array (not ft_strfree)

	TODO: Remplace variable (already exists)
			1. free string
			2. Move new string to the same address

	NOTE: export can only export variables while being executed from parent,
	if it is executed from a child (subshell), it will not change the parent env
	although it can export (display) child env from subshell.
	Reported from bash.

*/
void	exporter(t_shell *shell)
{
	int	i;
	int j;
	int	k;
	int end;

	char *name;
	char *value;

	name = get_name(shell);
	if (!name)
		return ;
	value = get_value(shell);
	if (!value)
		return ;
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
			if (shell->env[i][ft_strlen(name)] == '=')
			{
				j+=2;
				while (shell->env[i][j] || value[k])
					shell->env[i][j++] = value[k++];
			}
		}
		shell->env[end] = ft_strjoin(name, "=");
		shell->env[end] = ft_strjoin(shell->env[end], value);
		shell->env[end+1] = NULL;
		i++;
	}
}
