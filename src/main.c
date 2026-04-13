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

int	main(int ac, char **av, char **envp)
{
	int pid;
	int status;
	if (ac > 1)
		return (ft_printf("No args"), 1);
	if (!av)
		return (1);
	char *line;
	line = readline("$: ");
	while (true) // shouldnt be true = func that will wait for keypress like CTRL+C
	{
		pid = fork();
		if (pid == 0)
			exec_cmd(line, envp);
		waitpid(pid, &status , 0 );
		line = readline("$: ");
	}
	return (0);
}
