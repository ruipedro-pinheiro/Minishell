/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:16:03 by saouissi          #+#    #+#             */
/*   Updated: 2026/03/09 16:21:27 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	correcter(char const *s1, char s, int c)
{
	int	x;

	x = 0;
	while (x < c)
	{
		if (s1[x] == s)
			return (1);
		x++;
	}
	return (0);
}

static int	checker(char const *s1, char const *set)
{
	int	x;
	int	y;
	int	z;

	x = 0;
	y = 0;
	z = 0;
	while (s1[x])
	{
		while (set[y])
		{
			while (correcter(set, set[y], y) == 1)
				y++;
			if (s1[x] == set[y])
				z++;
			if (set[y] != 0)
				y++;
		}
		if (x == z || s1[x + 1] == 0)
			return (z);
		y = 0;
		x++;
	}
	return (0);
}

static int	checkersequel(char const *s1, char const *set)
{
	int	x;
	int	y;
	int	z;

	x = ft_strlen(s1) - 1;
	y = 0;
	z = ft_strlen(s1) - 1;
	while (x >= 0)
	{
		while (set[y])
		{
			while (correcter(set, set[y], y) == 1)
				y++;
			if (s1[x] == set[y])
				z--;
			if (set[y] != 0)
				y++;
		}
		if (x == z)
			return (ft_strlen(s1) - z - 1);
		y = 0;
		x--;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		a;
	int		b;
	int		x;
	char	*trim;

	x = 0;
	a = checker(s1, set);
	b = checkersequel(s1, set);
	trim = malloc((ft_strlen(s1) - (a + b) + 1));
	if (!trim)
		return (0);
	while (s1[a + x] && a + x < (int)ft_strlen(s1) - b)
	{
		trim[x] = s1[a + x];
		x++;
	}
	trim[x] = 0;
	return (trim);
}
