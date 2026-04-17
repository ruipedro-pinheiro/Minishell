/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:10:32 by saouissi          #+#    #+#             */
/*   Updated: 2025/11/03 18:04:28 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	flagger(const char *big, const char *little, size_t len, size_t z)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (little[x])
	{
		if (big[z + x] != little[x] || (z + x) >= len)
			y = 1;
		x++;
	}
	return (y);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		x;
	size_t		y;
	size_t		z;

	y = 0;
	x = 0;
	z = 0;
	if (little[z] == '\0')
		return ((char *)big);
	while (big[z] != '\0' && z < len)
	{
		if (big[z] == little[x])
		{
			y = flagger(big, little, len, z);
			if (y == 0)
				return ((char *)&big[z]);
			y = 0;
			x = 0;
		}
		z++;
	}
	return (0);
}
