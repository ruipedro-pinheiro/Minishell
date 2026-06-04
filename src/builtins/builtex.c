/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:31:38 by saouissi          #+#    #+#             */
/*   Updated: 2026/06/03 18:43:42 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtex(t_shell *shell)
{
	// if (shell->cmds->cmd_args[0]
		// && ft_strncmp(shell->cmds->cmd_args[0], "cd", 3) == 0)
		// return (cder(shell), exit(shell->exit_status));
	if (shell->cmds->cmd_args[0]
		&& ft_strncmp(shell->cmds->cmd_args[0], "env", 4) == 0)
		return (envinator(shell), exit(shell->exit_status));
	if (shell->cmds->cmd_args[0]
		&& ft_strncmp(shell->cmds->cmd_args[0], "pwd", 4) == 0)
		return (pwder(shell), exit(shell->exit_status));
	// if (shell->cmds->cmd_args[0]
		// && ft_strncmp(shell->cmds->cmd_args[0], "export", 7) == 0)
		// return (exiter(shell), exit(shell->exit_status));
	if (shell->cmds->cmd_args[0]
		&& ft_strncmp(shell->cmds->cmd_args[0], "export", 5) == 0)
		return(exporter(shell, "nom", "valeur"), exit(shell->exit_status));
	// if (shell->cmds->cmd_args[0]
		// && ft_strncmp(shell->cmds->cmd_args[0], "unset", 6) == 0)
		// return (exiter(shell), exit(shell->exit_status));
	// if (shell->cmds->cmd_args[0]
		// && ft_strncmp(shell->cmds->cmd_args[0], "echo", 5) == 0)
		// return (exiter(shell), exit(shell->exit_status));
}
