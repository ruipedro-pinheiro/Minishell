/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/05/15 19:22:52 by saouissi         ###   ########.fr       */
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

// read(fd, a, 0); is for testing only if the file is readable.
// it might not be safe.

void	historer(t_shell *shell)
{
	char	*a;
	char	*b;
	int		fd;

	fd = open(".minishell_history", O_RDONLY);
	if (!fd)
		return ;
	a = ft_strdup("");
	while (true)
	{
		a = get_next_line(fd);
		if (shell->historian)
			b = ft_strjoin(shell->historian, a);
		else
			b = a;
		if (!a)
			break ;
		free(shell->historian);
		shell->historian = b;
		free(a);
	}
	close(fd);
}
