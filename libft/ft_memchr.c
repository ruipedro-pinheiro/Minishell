/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:11:51 by saouissi          #+#    #+#             */
/*   Updated: 2025/11/03 18:03:16 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			x;
	unsigned char	*a;

	a = (unsigned char *)s;
	x = 0;
	if (n == 0)
		return (0);
	while (c > 127)
		c -= 256;
	while (n-- > 0)
	{
		if (a[x] == (unsigned char)c)
			return (&a[x]);
		x++;
	}
	return (0);
}
