/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 13:43:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/14 18:32:18 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>

static int	is_numeric(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	print_err(t_shell *shell, char **args, int i)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(args[i], 2);
	ft_putendl_fd(": numeric argument required", 2);
	shell->exit_status = 2;
}

void	check_overflow(t_shell *shell, char **args, int i)
{
	long long	exit_number;
	bool		overflow;

	if (args[i])
	{
		exit_number = ((ft_atoll(args[1], &overflow) % 256) + 256) % 256;
		if (overflow)
		{
			print_err(shell, args, i);
			shell->exit_status = 2;
		}
		else
			shell->exit_status = exit_number;
	}
}

void	exit_minishell(t_shell *shell)
{
	char	**args;

	args = shell->cmds->cmd_args;
	if (!args[0] || ft_strncmp(args[0], "exit", 5) != 0)
		return ;
	check_overflow(shell, args, 1);
	if (args[1] && !is_numeric(args[1]))
		print_err(shell, args, 1);
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->exit_status = 1;
		return ;
	}
	exiter(shell);
}
