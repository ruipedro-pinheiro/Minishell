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

char	*get_value(char *arg)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arg[i] != '=')
		i++;
	i++;
	if (arg[i] == '\0')
		return (NULL);
	value = malloc(sizeof(char) * i + 1);
	if (!value)
		return (NULL);
	while (arg[j])
	{
		value[j] = arg[j];
		j++;
	}
	value[j] = '\0';
	return (value);
}

char	*get_name(char *arg)
{
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arg[i] != '=')
		i++;
	name = malloc(sizeof(char) * j);
	if (!name)
		return (NULL);
	while (arg[i] != '=')
	{
		name[j] = arg[j];
		j++;
	}
	name[j] = '\0';
	return (name);
}

/*
   TODO: Sort alphabetically all the env to display correctly
		1. Maybe use ft_strncmp ?
*/
void	display_export(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd("declare -x ", 2);
		ft_putendl_fd(shell->env[i], 2);
		i++;
	}
}

int	find_env_var(char **env, char *name)
{
	(void)env;
	(void)name;
	return (1);
}

/*
		TODO: Remplace variable (already exists)
				1. free string
				2. Move new string to the same address
 */
void	modify_env(t_shell *shell, int index, char *value)
{
	(void)shell;
	(void)index;
	(void)value;
}

/*
		TODO: Add variable (if not existing already)
			1. Count size of n
			2. Malloc new array of n + 2
			3. Copy pointers (no strdup)
			4. case n = name=value (ft_strjoin), case n+1 = NULL
			5. free array (not ft_strfree)
*/
void	add_to_env(t_shell *shell, char *name, char *value)
{
	(void)shell;
	(void)name;
	(void)value;
}

/*
	TODO: divide funtion into multiple functions
			1. Export value
			2. Check how many vars are exported from same command:
					export var="val" ls="ls -la" = 2 variables
			3. Parsing value and data from cmds

	NOTE: export can only export variables while being executed from parent,
	if it is executed from a child (subshell), it will not change the parent env
	although it can export (display) child env from subshell.
	Reported from bash.

*/

void	exporter(t_shell *shell)
{
	int		i;
	int		j;
	int		k;
	int		end;
	char	*name;
	char	*value;


	display_export(shell);
	name = "a";
	value = "1";
	end = -1;
	j = 0;
	i = 0;
	k = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0)
		{
			if (shell->env[i][ft_strlen(name)] == '=')
			{
				j += 2;
				while (shell->env[i][j] || value[k])
					shell->env[i][j++] = value[k++];
			}
		}
		shell->env = malloc(sizeof(char *) * count_fields(*shell->env));
		shell->env[end] = ft_strjoin(name, "=");
		shell->env[end] = ft_strjoin(shell->env[end], value);
		shell->env[end + 1] = NULL;
		i++;
	}
}
