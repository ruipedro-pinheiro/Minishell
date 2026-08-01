/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:51:39 by pedro             #+#    #+#             */
/*   Updated: 2026/07/21 19:40:23 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*add_git(void)
{
	int		fd;
	int		i;
	char	buf[64];
	char	*name;

	fd = open(".git/HEAD", O_RDONLY);
	if (fd == -1)
		return (ft_strdup(""));
	i = read(fd, buf, 63);
	buf[i - 1] = '\0';
	if (ft_strrchr(buf, '/'))
	{
		name = ft_strdup(" ");
		name = ft_strapnd(name, ft_strrchr(buf, '/') + 1);
		close(fd);
		return (name);
	}
	else
	{
		close(fd);
		name = NULL;
		return (name);
	}
}

char	*add_home(char *path)
{
	char	*home;

	home = getenv("HOME");
	if (ft_strncmp(path, home, ft_strlen(home)) == 0)
		return (ft_strjoin("~", path + ft_strlen(home)));
	return (ft_strdup(path));
}

char	*set_exit_status(t_shell *shell)
{
	if (shell->exit_status == 0)
		return (ft_strdup("❯" RESET));
	else
		return (ft_strdup(""RED"❯" RESET));
}

char	*prompt_display(t_shell *shell)
{
	char	*prompt;
	char	*tmp;

	if (!isatty(0))
		return (NULL);
	print_info();
	prompt = ft_strdup(SKY "╰─");
	tmp = set_exit_status(shell);
	prompt = ft_strapnd(prompt, tmp);
	free(tmp);
	return (prompt);
}

char	*prompt_readline(t_shell *shell)
{
	char	*display;
	char	*line;

	print_prompt_sp();
	display = prompt_display(shell);
	line = readline(display);
	free(display);
	if (g_signal == SIGINT)
	{
		shell->exit_status = 130;
		g_signal = 0;
	}
	return (line);
}
