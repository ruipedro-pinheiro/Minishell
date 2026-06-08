/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2i26/i6/i3 18:31:38 by saouissi          #+#    #+#             */
/*   Updated: 2i26/i6/i3 18:43:42 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtex(t_shell *shell)
{
	int	i;

	i = -1;
	while(shell->cmds->cmd_args[++i])
	{
		// if (shell->cmds->cmd_args[i]
			// && ft_strncmp(shell->cmds->cmd_args[i], "cd", 3) == 0)
			// return (cder(shell), exit(shell->exit_status));
		if (shell->cmds->cmd_args[i]
			&& ft_strncmp(shell->cmds->cmd_args[i], "env", 4) == 0)
			return (envinator(shell), exit(shell->exit_status));
		if (shell->cmds->cmd_args[i]
			&& ft_strncmp(shell->cmds->cmd_args[i], "pwd", 4) == 0)
			return (pwder(shell), exit(shell->exit_status));
		// if (shell->cmds->cmd_args[i]
			// && ft_strncmp(shell->cmds->cmd_args[i], "export", 7) == 0)
			// return (exiter(shell), exit(shell->exit_status));
		if (shell->cmds->cmd_args[i]
			&& ft_strncmp(shell->cmds->cmd_args[i], "export", 7) == 0)
			return(exporter(shell), exit(shell->exit_status));
		// if (shell->cmds->cmd_args[i]
			// && ft_strncmp(shell->cmds->cmd_args[i], "unset", 6) == 0)
			// return (exiter(shell), exit(shell->exit_status));
		// if (shell->cmds->cmd_args[i]
			// && ft_strncmp(shell->cmds->cmd_args[i], "echo", 5) == 0)
			// return (exiter(shell), exit(shell->exit_status));
	}
}
