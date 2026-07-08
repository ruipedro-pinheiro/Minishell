/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:41:17 by saouissi          #+#    #+#             */
/*   Updated: 2026/07/08 19:36:12 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
   TODO: Sort alphabetically all the env to display correctly
*/
void	export_dup(t_shell *shell)
{
	int		n;
	int		i;
	char	**tmp_env;

	n = 0;
	i = 0;
	while (shell->env[n])
		n++;
	tmp_env = malloc(sizeof(char *) * (n + 1));
	if (!tmp_env)
		return ;
	while (shell->env[i])
	{
		tmp_env[i] = shell->env[i];
		i++;
	}
	tmp_env[i] = NULL;
	sort_env(tmp_env);
	free(tmp_env);
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

	name = get_name(shell->env[index]);
	new_var = ft_strapnd(name, "=");
	new_var = ft_strapnd(new_var, value);
	free(shell->env[index]);
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
		new_env[i] = ft_strapnd(new_env[i], value);
	}
	i++;
	new_env[i] = NULL;
	free(shell->env);
	shell->env = new_env;
}

static void	export_one(t_shell *shell, char *arg)
{
	char	*name;
	char	*value;
	int		env_indx;

	if (!is_name_valid(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return ;
	}
	name = get_name(arg);
	value = get_value(arg);
	env_indx = find_env_var(shell->env, name);
	if (env_indx != -1)
	{
		if (value)
			modify_env(shell, env_indx, value);
	}
	else
		add_to_env(shell, name, value);
	free(name);
	free(value);
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
	char	*arg;

	arg_indx++;
	if (!shell->cmds->cmd_args[arg_indx])
	{
		export_dup(shell);
		return ;
	}
	while (shell->cmds->cmd_args[arg_indx])
	{
		arg = shell->cmds->cmd_args[arg_indx];
		export_one(shell, arg);
		arg_indx++;
	}
}
