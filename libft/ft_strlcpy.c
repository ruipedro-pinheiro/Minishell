/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:10:55 by saouissi          #+#    #+#             */
/*   Updated: 2025/11/03 18:04:15 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	x;
	size_t			y;

	y = 0;
	x = 0;
	while (src[y])
		y++;
	if (size == 0)
		return (y);
	while (src[x] != '\0' && x < size - 1)
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (y);
}
