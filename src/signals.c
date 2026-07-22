/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:55:09 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/21 15:35:28 by pedro            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal;

void	sigint_handler(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	print_info();
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	(void)sig;
	write(2, "Quit (core dumped)", 19);
}

void	set_signal_mode(t_signal_modes mode)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (mode == INTERACTIVE)
	{
		sa.sa_handler = sigint_handler;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == EXECUTION)
	{
		sa.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == FORKED)
	{
		sa.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}
