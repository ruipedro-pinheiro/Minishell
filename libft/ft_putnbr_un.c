/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_un.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:32:31 by saouissi          #+#    #+#             */
/*   Updated: 2026/04/13 16:46:47 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_un(int n, int fd)
{
	long	nb;
	char	a;
	int		y;

	y = 1;
	nb = n;
	if (n < 0)
	{
		nb += 4294967296;
	}
	if (nb >= 10)
		y += ft_putnbr_un(nb / 10, fd);
	a = nb % 10 + '0';
	write(fd, &a, 1);
	return (y);
}
