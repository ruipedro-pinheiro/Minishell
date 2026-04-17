/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:07:06 by saouissi          #+#    #+#             */
/*   Updated: 2025/11/03 18:03:41 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			x;
	unsigned char	*a;

	a = (unsigned char *)s;
	x = 0;
	while (x < n)
	{
		*a = (unsigned char)c;
		a++;
		x++;
	}
	return (s);
}
