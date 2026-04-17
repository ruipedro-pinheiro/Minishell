/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:11:26 by saouissi          #+#    #+#             */
/*   Updated: 2025/11/03 18:03:27 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			x;
	char			*a;
	const char		*b;

	b = (const char *)src;
	a = (char *)dest;
	if (n == 0)
		return (dest);
	if (!dest && !src)
		return (0);
	x = n - 1;
	if (dest > src)
	{
		while (x > 0)
		{
			a[x] = b[x];
			x--;
		}
		a[x] = b[x];
	}
	else
		ft_memcpy(a, b, n);
	return (dest);
}
