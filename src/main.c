/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/08 19:08:03 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **environ)
{
	t_shell	shell;

	if (ac > 1 && av[0])
		return (0);
	shell.historian = ft_strdup("");
	historer(&shell);
	shell.env = enver(environ);
	shell.exit_status = 0;
	shell.cmds = NULL;
	set_prompt(&shell);
	if (shell.cmds)
		free_cmds(shell.cmds);
	free(shell.historian);
	return (0);
}

char	**enver(char **environ)
{
	char	**env;
	int		i;

	i = -1;
	while (environ[++i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = -1;
	while (environ[++i])
	{
		env[i] = ft_strdup(environ[i]);
		if (!env[i])
			return (ft_strfree(env), NULL);
	}
	env[i] = NULL;
	return (env);
}
