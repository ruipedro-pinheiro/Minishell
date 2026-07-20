/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro </var/spool/mail/pedro>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:51:39 by pedro             #+#    #+#             */
/*   Updated: 2026/07/15 18:05:25 by pedro            ###   ########.ch       */
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

	prompt = ft_strdup(SKY "╭─Minishell •" MAUVE);
	prompt = ft_strapnd(prompt, "  ");
	prompt = ft_strapnd(prompt, getenv("USER"));
	prompt = ft_strapnd(prompt, GREY " • " SKY);
	prompt = ft_strapnd(prompt, " ");
	tmp = add_home(variable_expansion("PWD", shell));
	prompt = ft_strapnd(prompt, tmp);
	free(tmp);
	tmp = add_git();
	if (tmp && tmp[0] != '\0')
	{
		prompt = ft_strapnd(prompt, GREY " • " PEACH);
		prompt = ft_strapnd(prompt, tmp);
		free(tmp);
	}
	else
		free(tmp);
	prompt = ft_strapnd(prompt, SKY "\n╰─");
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
	return (line);
}
