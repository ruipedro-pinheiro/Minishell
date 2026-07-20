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
                    ╭───────────────────────╮\n\
                    │   " PEACH "=== MINISHELL === " MAUVE "  │\n\
                    │   " GREY "By: Sami & Pedro " MAUVE "   │\n\
                    ╰───────────────────────╯\n");
}
