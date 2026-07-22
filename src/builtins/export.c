/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:40:55 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/14 18:36:47 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		shell->exit_status = 1;
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

void	exporter(t_shell *shell, int arg_indx)
{
	char	*arg;

	shell->exit_status = 0;
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
