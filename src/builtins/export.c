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
// do i malloc a whole new string with variable=name ?
// or do i change directly the string without malloc ?!
// i need to see if there is any issues with overflow
//		if new value is bigger than actual then yes -> overflow.

void	modify_env(t_shell *shell, int index, char *value)
{
	char	*name;
	char	*new_var;

	new_var = ft_strdup("");
	if (!new_var)
		return ;
	name = get_name(shell->env[index]);
	new_var = ft_strjoin(new_var, name);
	new_var = ft_strjoin(new_var, "=");
	new_var = ft_strjoin(new_var, value);
	free(shell->env[index]);
	free(name);
	shell->env[index] = new_var;
}

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
	if (!value)
		new_env[i] = ft_strdup(name);
	else
	{
		new_env[i] = ft_strjoin(name, "=");
		new_env[i] = ft_strjoin(new_env[i], value);
	}
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
	env_indx = 0;
	if (!shell->cmds->cmd_args[arg_indx])
	{
		display_export(shell);
		return ;
	}
	while (shell->cmds->cmd_args[arg_indx])
	{
		arg = shell->cmds->cmd_args[arg_indx];
		env_indx = find_env_var(shell->env, get_name(arg));
		if (env_indx != 0)
			modify_env(shell, env_indx, get_value(arg));
		else if (env_indx == 0)
			add_to_env(shell, get_name(arg), get_value(arg));
		arg_indx++;
	}
}
