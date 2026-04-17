/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:11:04 by saouissi          #+#    #+#             */
/*   Updated: 2025/11/03 18:04:12 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t			x;
	size_t			y;
	size_t			z;

	y = 0;
	x = ft_strlen(dest);
	z = ft_strlen(src);
	if (size > x)
	{
		while (src[y] != '\0' && (y + x < size - 1))
		{
			dest[x + y] = src[y];
			y++;
		}
		dest[x + y] = '\0';
		return (x + z);
	}
	else
		return (z + size);
}
