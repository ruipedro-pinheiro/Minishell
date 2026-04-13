/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:16:56 by saouissi          #+#    #+#             */
/*   Updated: 2026/04/13 19:25:49 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	trimmer(char **a)
{
	int		x;
	char	*b;

	x = 0;
	while (a[x])
	{
		if (a[x][0] == '\'')
		{
			b = ft_strtrim(a[x], "\'");
			a[x] = b;
		}
		x++;
	}
}

void	exer(char *cmd, char **env)
{
	char	**splitcmd;
	char	*path;

	splitcmd = ft_split(cmd, ' ');
	if (!splitcmd[0])
	{
		ft_strfree(splitcmd);
		exit(127);
	}
	trimmer(splitcmd);
	path = get_path(splitcmd[0]);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_strfree(splitcmd);
		exit(127);
	}
	if (execve(path, splitcmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(splitcmd[0], 2);
		ft_strfree(splitcmd);
		exit(126);
	}
}

void	parent(char **argv, char **env)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	exer(argv[2], env);
}
