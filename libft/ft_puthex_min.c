/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_min.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:29:04 by saouissi          #+#    #+#             */
/*   Updated: 2026/04/13 16:46:31 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_min(int n, int fd)
{
	long	x;
	char	a;
	int		y;

	y = 1;
	x = n;
	if (x < 0)
	{
		x += 4294967296;
	}
	if (x >= 16)
		y += ft_puthex_min(x / 16, fd);
	if (x % 16 < 10)
		a = x % 16 + '0';
	else
		a = x % 16 + 87;
	write(fd, &a, 1);
	return (y);
}
