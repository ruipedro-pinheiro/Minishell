/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:11:46 by saouissi          #+#    #+#             */
/*   Updated: 2025/11/03 18:03:19 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	x;

	x = 0;
	while (x < n)
	{
		if (((unsigned char *)s1)[x] != ((unsigned char *)s2)[x])
			return (((unsigned char *)s1)[x] - ((unsigned char *)s2)[x]);
		x++;
	}
	return (0);
}
