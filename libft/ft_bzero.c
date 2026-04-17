/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:19:52 by saouissi          #+#    #+#             */
/*   Updated: 2025/11/03 18:02:48 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			x;
	unsigned char	*a;

	a = (unsigned char *)s;
	x = 0;
	while (x < n)
	{
		*a = 0;
		a++;
		x++;
	}
}
