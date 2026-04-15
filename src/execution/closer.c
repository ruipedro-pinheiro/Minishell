/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:30:12 by saouissi          #+#    #+#             */
/*   Updated: 2026/04/15 18:42:54 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	destroyer(t_shell *shell) // purpose is to destroy all allocations within t_shell whenever exit

void	exiter(t_shell *shell)
{
	int	fd;

	fd = open(".minishell_history", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_putstr_fd(shell->historian, fd);
	destroyer(shell); // refer to up
	exit(shell->exit_status);
}
