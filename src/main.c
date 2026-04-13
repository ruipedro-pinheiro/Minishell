/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/13 13:04:36 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
		t_pipex	pipex;

	if (ac < 5)
		return (ft_putstr_fd("Error: bad arguments\n", 2), 1);
	if (ft_strncmp(av[1], "here_doc", 9) == 0 && ac < 6)
		return (ft_putstr_fd("Error: bad arguments\n", 2), 1);
	init_pipex(&pipex, ac, av, env);
	return (pipe_setup(&pipex));
}
