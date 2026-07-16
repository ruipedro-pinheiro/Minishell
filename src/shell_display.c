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

static int	ft_putchar_tc(int i)
{
	return (write(1, &i, 1));
}

static void	clean_screen(void)
{
	char	buf[1024];
	char	capbuf[64];
	char	*area;
	char	*cl;
	char	*term;

	term = getenv("TERM");
	if (!term || tgetent(buf, term) <= 0)
	{
		printf("\e[1;1H\e[2J");
		return ;
	}
	area = capbuf;
	cl = tgetstr("cl", &area);
	if (cl)
		tputs(cl, 1, ft_putchar_tc);
}

void	print_banner(void)
{
	if (!isatty(0))
		return ;
	clean_screen();
	ft_printf(""MAUVE"\
                    ╭───────────────────────╮\n\
                    │   " PEACH "=== MINISHELL === " MAUVE "  │\n\
                    │   " GREY "By: Sami & Pedro " MAUVE "   │\n\
                    ╰───────────────────────╯\n");
}
