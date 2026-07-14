/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 13:43:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/06/03 19:28:32 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	exit_minishell(t_shell *shell)
{
	char	**args;

	args = shell->cmds->cmd_args;
	if (!args[0] || ft_strncmp(args[0], "exit", 5) != 0)
		return ;
	if (args[1] && !is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		shell->exit_status = 2;
		exiter(shell);
	}
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->exit_status = 1;
		return ;
	}
	if (args[1])
		shell->exit_status = ((ft_atoll(args[1]) % 256) + 256) % 256;
	exiter(shell);
}
