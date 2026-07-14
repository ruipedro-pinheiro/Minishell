/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:34:28 by saouissi          #+#    #+#             */
/*   Updated: 2026/07/06 19:28:37 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	envinator(t_shell *shell)
{
	int	x;

	x = 0;
	while (shell->env[x])
	{
		printf("%s\n", shell->env[x]);
		x++;
	}
}
