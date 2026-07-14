/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pexiter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 18:57:01 by saouissi          #+#    #+#             */
/*   Updated: 2026/07/14 19:00:41 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pexiter(char **s_cmd, char *error_msg)
{
	ft_strfree(s_cmd);
	free(error_msg);
	exit(127);
}
