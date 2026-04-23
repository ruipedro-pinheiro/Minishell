/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:30:12 by saouissi          #+#    #+#             */
/*   Updated: 2026/04/23 18:11:50 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// free(shell->infile);
// free(shell->outfile);
// free(shell->limiter);
// ft_strfree(shell->cmds->cmd_args);
// purpose is to destroy all allocations within t_shell whenever exit
void	destroyer(t_shell *shell)
{
	free(shell->historian);
}

void	exiter(t_shell *shell)
{
	int	fd;

	fd = open(".minishell_history", O_APPEND | O_WRONLY | O_CREAT, 0644);
	ft_putstr_fd(shell->historian, fd);
	destroyer(shell);
	exit(shell->exit_status);
}
