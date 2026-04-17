/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:11:38 by saouissi          #+#    #+#             */
/*   Updated: 2025/11/03 18:03:23 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				x;
	unsigned char		*a;
	const unsigned char	*b;

	b = (const unsigned char *)src;
	a = (unsigned char *)dest;
	x = 0;
	if (!dest && !src)
		return (0);
	while (x < n)
	{
		*a = *b;
		b++;
		a++;
		x++;
	}
	return (dest);
}
