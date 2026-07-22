/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:06:19 by saouissi          #+#    #+#             */
/*   Updated: 2026/07/16 19:19:04 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwder(t_shell *shell)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell: pwd");
		shell->exit_status = 1;
		return ;
	}
	printf("%s\n", cwd);
	shell->exit_status = 0;
}
