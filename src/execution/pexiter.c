/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pexiter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 18:57:01 by saouissi          #+#    #+#             */
/*   Updated: 2026/07/24 19:55:42 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pexiter(char *error_msg, t_shell *shell)
{
	free(error_msg);
	clean_exit(shell, 127);
}
