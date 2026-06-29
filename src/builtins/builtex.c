/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:31:38 by saouissi          #+#    #+#             */
/*   Updated: 2026/06/10 18:16:40 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtex(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->cmds->cmd_args[++i])
	{
		if (shell->cmds->cmd_args[i]
			&& ft_strncmp(shell->cmds->cmd_args[i], "cd", 3) == 0)
			return (cder(shell), shell->exit_status);
		if (shell->cmds->cmd_args[i]
			&& ft_strncmp(shell->cmds->cmd_args[i], "env", 4) == 0)
			return (envinator(shell), shell->exit_status);
		if (shell->cmds->cmd_args[i]
			&& ft_strncmp(shell->cmds->cmd_args[i], "pwd", 4) == 0)
			return (pwder(shell), shell->exit_status);
		if (shell->cmds->cmd_args[i]
			&& ft_strncmp(shell->cmds->cmd_args[i], "export", 7) == 0)
			return (exporter(shell, i), shell->exit_status);
		if (shell->cmds->cmd_args[i]
			&& ft_strncmp(shell->cmds->cmd_args[i], "unset", 6) == 0)
			return (unset(shell, i), shell->exit_status);
	}
	return (-1);
}

// -1 = no builtin executed = no need to use exit_status = we can execute pipex
//
// TODO: find a way to make work builtins after pipes (in subshells/childs)
