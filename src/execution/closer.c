/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:30:12 by saouissi          #+#    #+#             */
/*   Updated: 2026/04/14 16:55:16 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exiter(t_pipex *pipex, int x)
{
	int	fd;

	fd = open(".minishell_history", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_putstr_fd(pipex->prompt, fd);
	exit(x);
}
