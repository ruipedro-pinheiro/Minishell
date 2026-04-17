/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:12:08 by saouissi          #+#    #+#             */
/*   Updated: 2025/11/03 18:02:44 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	x;
	int	pone;
	int	all;

	x = 0;
	pone = 1;
	all = 0;
	while ((nptr[x] == 32) || (nptr[x] >= 9 && nptr[x] <= 13))
		x++;
	if (((nptr[x] == '-') || (nptr[x] == '+'))
		&& ((nptr[x + 1] == '-') || (nptr[x + 1] == '+')))
		return (all);
	if (nptr[x] == '-' || nptr[x] == '+')
	{
		if (nptr[x] == '-')
			pone *= -1;
		x++;
	}
	while (nptr[x] >= 48 && nptr[x] <= 57)
	{
		all = (all * 10) + (nptr[x] - 48);
		x++;
	}
	return (all * pone);
}
