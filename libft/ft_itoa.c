/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:11:22 by saouissi          #+#    #+#             */
/*   Updated: 2026/03/09 16:22:41 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mallocer(int n)
{
	long	n2;
	int		x;

	x = 1;
	n2 = n;
	if (n <= 0)
	{
		n2 = -n2;
		x++;
	}
	while (n2 != 0)
	{
		n2 = n2 / 10;
		x++;
	}
	return (x);
}

static char	*itwoa(int n, char *a, int x)
{
	long	nb;

	nb = n;
	if (nb >= 10)
		itwoa(nb / 10, a, x - 1);
	a[x] = nb % 10 + '0';
	return (a);
}

char	*ft_itoa(int n)
{
	char	*a;
	int		x;
	long	nb;

	x = 0;
	nb = n;
	a = malloc(sizeof(char) * mallocer(n));
	if (!a)
		return (0);
	x = mallocer(n) - 2;
	if (nb < 0)
	{
		nb = -nb;
		a[0] = '-';
	}
	if (nb >= 10)
		itwoa(nb / 10, a, x - 1);
	a[x] = nb % 10 + '0';
	a[mallocer(n) - 1] = '\0';
	return (a);
}
