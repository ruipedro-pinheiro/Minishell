/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:40:55 by rpinheir          #+#    #+#             */
/*   Updated: 2026/06/10 14:23:33 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

/*
   TODO: Sort alphabetically all the env to display correctly
*/
void	display_export(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(shell->env[i], 1);
		i++;
	}
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
			4. case n = name=value (ft_strarg_indxoin), case n+1 = NULL
			5. free array (not ft_strfree)
*/
void	add_to_env(t_shell *shell, char *name, char *value)
{
	char	**new_env;
	int		i;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = -1;
	while (shell->env[++i])
		new_env[i] = shell->env[i];
	new_env[i] = ft_strjoin(name, "=");
	new_env[i] = ft_strjoin(new_env[i], value);
	i++;
	new_env[i] = NULL;
	free(shell->env);
	shell->env = new_env;
}

/*
TODO: Main exporter orchestration
		1. Check if export is from child or parent (with i)
			a. if yes = only display env
				(modifying anything on child is irrelevant)
				i still let it modify subshell env in case bash does the same
		2. find if the variable is already on env
			Exporter does only one cmd per cmd
					([export] [ls="ls -la"] [dir="my dir"] etc...)
			a. if it exists -> modify only the value
			b. if it doesn't exist :
				realloc new array and add enough space to add new variable
*/
void	exporter(t_shell *shell, int arg_indx)
{
	int		env_indx;
	char	*arg;

	arg_indx++;
	arg = shell->cmds->cmd_args[arg_indx];
	env_indx = 0;
	if (!shell->cmds->cmd_args[arg_indx])
	{
		display_export(shell);
		return ;
	}
	while (shell->cmds->cmd_args[arg_indx])
	{
		env_indx = find_env_var(shell->env, get_name(arg));
		printf("ENV INDEX = %d \n", env_indx);
		if (env_indx != 0)
			modify_env(shell, env_indx, get_value(arg));
		else if (env_indx == 0)
			add_to_env(shell, get_name(arg), get_value(arg));
		arg_indx++;
	}
}
