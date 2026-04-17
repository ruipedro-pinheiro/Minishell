/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:58:02 by saouissi          #+#    #+#             */
/*   Updated: 2026/04/13 16:46:42 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putbin_fd(int n, int fd)
{
	long	x;
	char	a;
	int		y;

	y = 1;
	x = n;
	if (x < 0)
	{
		write(fd, "-", 1);
		x = -x;
	}
	if (x >= 2)
		y += ft_putbin_fd(x / 2, fd);
	a = x % 2 + '0';
	write(fd, &a, 1);
	return (y);
}

static int	ft_putoct_fd(int n, int fd)
{
	long	x;
	char	a;
	int		y;

	y = 1;
	x = n;
	if (x < 0)
	{
		write(fd, "-", 1);
		x = -x;
	}
	if (x >= 8)
		y += ft_putoct_fd(x / 8, fd);
	a = x % 8 + '0';
	write(fd, &a, 1);
	return (y);
}

static int	ft_puthex_fd(int n, int fd)
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
		y += ft_puthex_fd(x / 16, fd);
	if (x % 16 < 10)
		a = x % 16 + '0';
	else
		a = x % 16 + 55;
	write(fd, &a, 1);
	return (y);
}

static int	ft_putnbr_c(int n, int fd)
{
	long	x;
	char	a;
	int		y;

	x = n;
	y = 1;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
		y = 2;
	}
	if (n >= 10)
		y += ft_putnbr_c(n / 10, fd);
	a = n % 10 + '0';
	write(fd, &a, 1);
	return (y);
}

int	ft_putnbr_base(int nbr, char *base, int fd)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (base[x])
		x++;
	if (x == 16)
		y += ft_puthex_fd(nbr, fd);
	else if (x == 10)
		y += ft_putnbr_c(nbr, fd);
	else if (x == 2)
		y += ft_putbin_fd(nbr, fd);
	else if (x == 8)
		y += ft_putoct_fd(nbr, fd);
	return (y);
}
