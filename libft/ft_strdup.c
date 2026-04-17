/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:31:32 by saouissi          #+#    #+#             */
/*   Updated: 2026/03/09 16:21:56 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		x;
	char	*clo;

	x = 0;
	clo = 0;
	while (src[x])
		x++;
	clo = malloc(sizeof(char) * (x + 1));
	if (!clo)
		return (0);
	x = 0;
	while (src[x])
	{
		clo[x] = src[x];
		x++;
	}
	clo[x] = '\0';
	return (clo);
}
