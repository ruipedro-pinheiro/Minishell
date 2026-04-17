/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/17 18:06:25 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	scribe(t_shell *shell, char *prompt)
{
	char	*a;

	a = ft_strjoin(shell->historian, prompt);
	free(shell->historian);
	shell->historian = a;
	a = ft_strjoin(shell->historian, "\n");
	free(shell->historian);
	shell->historian = a;
}

void	historer(t_shell *shell)
{
	char	*a;
	char	*b;
	int		fd;

	fd = open(".minishell_history", O_RDONLY);
	if (fd > 0)
	{
		while ((a = get_next_line(fd))) //
		{
			b = ft_strjoin(shell->historian, a);
			free(shell->historian);
			shell->historian = b;
			free(a);
		}
		close(fd);
	}
}

