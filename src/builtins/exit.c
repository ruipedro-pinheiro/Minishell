/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 13:43:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/05/05 14:34:44 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_minishell(t_shell *shell)
{
	if (shell->cmds->cmd_args[0]
		&& ft_strncmp(shell->cmds->cmd_args[0], "exit", 5) == 0)
		exiter(shell);
}
