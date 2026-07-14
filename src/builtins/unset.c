/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 12:00:00 by rpinheir          #+#    #+#             */
/*   Updated: 2026/06/29 11:15:16 by pedro            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: unset
//   - for each arg: locate the var via find_env_var
//   - remove the entry from shell->env (free + compact)
//   - silent if the var doesn't exist
void	unset(t_shell *shell, int arg_indx)
{
	int		env_indx;
	char	*name;

	while (shell->cmds->cmd_args[arg_indx])
	{
		name = shell->cmds->cmd_args[arg_indx];
		env_indx = find_env_var(shell->env, name);
		if (env_indx != -1)
		{
			free(shell->env[env_indx]);
			while (shell->env[env_indx])
			{
				shell->env[env_indx] = shell->env[env_indx + 1];
				env_indx++;
			}
		}
		arg_indx++;
	}
}
