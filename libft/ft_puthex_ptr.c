/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:29:04 by saouissi          #+#    #+#             */
/*   Updated: 2026/04/13 16:46:21 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthex_min2(unsigned long long int n, int fd)
{
	char	a;
	int		y;

	y = 1;
	if (n >= 16)
		y += ft_puthex_min2(n / 16, fd);
	if (n % 16 < 10)
		a = n % 16 + '0';
	else
		a = n % 16 + 87;
	write(fd, &a, 1);
	return (y);
}

int	ft_puthex_ptr(void *n, int fd)
{
	unsigned long long int	x;
	char					a;
	int						y;

	y = 3;
	if (n == 0)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	x = (unsigned long long int)n;
	write(fd, "0x", 2);
	if (x >= 16)
		y += ft_puthex_min2(x / 16, fd);
	if (x % 16 < 10)
		a = x % 16 + '0';
	else
		a = x % 16 + 87;
	write(fd, &a, 1);
	return (y);
}
