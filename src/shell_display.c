/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:27:24 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/15 18:47:35 by pedro            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_info(void)
{
	char	*prompt;
	char	*tmp;
	char	path[1024];

	if (!isatty(0))
		return ;
	prompt = ft_strdup(SKY "╭─Minishell •" MAUVE);
	prompt = ft_strapnd(prompt, "  ");
	prompt = ft_strapnd(prompt, getenv("USER"));
	prompt = ft_strapnd(prompt, GREY " • " SKY);
	prompt = ft_strapnd(prompt, " ");
	tmp = add_home(getcwd(path, sizeof(path)));
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
	(write(1, prompt, ft_strlen(prompt)), free(prompt), ft_putendl_fd("", 1));
}

void	print_prompt_sp(void)
{
	struct winsize	ws;
	int				i;

	if (!isatty(0))
		return ;
	ioctl(1, TIOCGWINSZ, &ws);
	write(1, "\033[7m%\033[0m", 9);
	i = 1;
	while (i < ws.ws_col)
	{
		write(1, " ", 1);
		i++;
	}
	write(1, "\r", 1);
	write(1, " ", 1);
	write(1, "\r", 1);
	write(1, "\n", 1);
}

void	print_banner(void)
{
	if (!isatty(0))
		return ;
	write(1, CLR_SCREEN, ft_strlen(CLR_SCREEN));
	ft_printf(""MAUVE"\
                    ╭──────────────────────────────────╮\n\
                    │                                  │\n\
                    │            " PEACH "\033[1mMINISHELL\033[22m" MAUVE "             │\n\
                    │   " GREY "\033[3m« As beautiful as a shell »\033[23m" MAUVE "    │\n\
                    │         " GREY "\033[2mby Sami & Pedro\033[22m" MAUVE "          │\n\
                    │                                  │\n\
                    ╰──────────────────────────────────╯" RESET "\n");
}
