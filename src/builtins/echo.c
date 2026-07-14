/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 12:00:00 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/14 18:31:22 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_n_option(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-' || arg[1] != 'n')
		return (false);
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (true);
	else
		return (false);
}

void	echoer(t_shell *shell, int arg_indx)
{
	char	*arg;

	shell->print_newline = true;
	arg_indx++;
	while (shell->cmds->cmd_args[arg_indx])
	{
		arg = shell->cmds->cmd_args[arg_indx];
		if (is_n_option(arg))
			shell->print_newline = false;
		else
			break ;
		arg_indx++;
	}
	while (shell->cmds->cmd_args[arg_indx])
	{
		ft_putstr_fd(shell->cmds->cmd_args[arg_indx], 1);
		if (shell->cmds->cmd_args[arg_indx + 1])
			ft_putstr_fd(" ", 1);
		arg_indx++;
	}
	if (shell->print_newline)
		ft_putendl_fd("", 1);
}
