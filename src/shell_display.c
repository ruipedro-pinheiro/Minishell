/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:27:24 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/14 17:28:54 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	ft_putendl_fd("Found term", 1);
	area = capbuf;
	cl = tgetstr("cl", &area);
	if (cl)
		tputs(cl, 1, ft_putchar_tc);
}

void	print_banner(void)
{
	clean_screen();
	ft_printf(""MAUVE"\
                    ╭───────────────────────╮\n\
                    │   " PEACH "=== MINISHELL === " MAUVE "  │\n\
                    │   " GREY "By: Sami & Pedro " MAUVE "   │\n\
                    ╰───────────────────────╯\n");
}
