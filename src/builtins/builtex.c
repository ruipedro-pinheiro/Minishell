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
	char	*cmd;

	cmd = shell->cmds->cmd_args[0];
	if (!cmd)
		return (-1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (cder(shell), shell->exit_status);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (envinator(shell), shell->exit_status);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (pwder(shell), shell->exit_status);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (exporter(shell, 0), shell->exit_status);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (unset(shell, 0), shell->exit_status);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (echoer(shell, 0), shell->exit_status);
	return (-1);
}
