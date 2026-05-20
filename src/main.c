/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/05/07 18:36:46 by saouissi         ###   ########.fr       */
/*   Updated: 2026/05/07 18:36:46 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	if (ac > 1 && av[0])
		return (ft_putendl_fd("Arguments are not permitted", 2), 0);
	shell.historian = ft_strdup("");
	historer(&shell);
	shell.env = env;
	shell.exit_status = 0;
	shell.cmds = NULL;
	set_prompt(&shell);
	if (shell.cmds)
		free_cmds(shell.cmds);
	free(shell.historian);
	return (0);
}
