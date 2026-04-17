/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:40:38 by saouissi          #+#    #+#             */
/*   Updated: 2026/04/13 16:47:04 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static int	ft_printchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

static int	ft_printstr(char *c, int fd)
{
	int	x;

	if (!c)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	x = 0;
	while (c[x])
		x++;
	write(fd, &*c, x);
	return (x);
}

static int	inter(int arg, int f)
{
	int	y;

	y = 0;
	if (f == 'c')
		y += ft_printchar_fd(arg, 1);
	if (f == 'd')
		y += ft_putnbr_base(arg, "0123456789", 1);
	if (f == 'i')
		y += ft_putnbr_base(arg, "0123456789", 1);
	if (f == 'u')
		y += ft_putnbr_un(arg, 1);
	if (f == 'x')
		y += ft_puthex_min(arg, 1);
	if (f == 'X')
		y += ft_putnbr_base(arg, "0123456789ABCDEF", 1);
	return (y);
}

static int	printer(va_list ap, int a)
{
	int	y;

	y = 0;
	if (a == 99 || a == 'd' || a == 'i' || a == 'u' || a == 'x' || a == 'X')
		y += inter(va_arg(ap, int), a);
	if (a == 's')
		y += ft_printstr(va_arg(ap, char *), 1);
	if (a == 'p')
		y += ft_puthex_ptr(va_arg(ap, void *), 1);
	if (a == 37)
		y += ft_printchar_fd(37, 1);
	return (y);
}

int	ft_printf(const char *f, ...)
{
	va_list	ap;
	int		x;
	int		y;

	y = 0;
	x = 0;
	va_start(ap, f);
	while (f[x])
	{
		if ((f[x] != 37 && f[x - 1] != 37) || (f[x] != 37 && f[x - 2] == 37))
			y += ft_printchar_fd(f[x], 1);
		if (f[x] == 37)
		{
			x++;
			if (f[x] != 0)
				y += printer(ap, f[x]);
		}
		x++;
	}
	va_end(ap);
	return (y);
}
