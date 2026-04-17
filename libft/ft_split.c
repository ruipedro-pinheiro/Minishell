/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:15:49 by saouissi          #+#    #+#             */
/*   Updated: 2026/03/19 17:14:58 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	liner(char const *s, char c)
{
	int	x;
	int	y;
	int	z;

	z = 0;
	y = 1;
	x = 0;
	if (s[0] == 0)
		return (0);
	if (s[0] == c)
		y = 0;
	while (s[x])
	{
		if (s[x] == '\'')
			z++;
		if (s[x] == c && s[x + 1] != c && s[x + 1] != 0)
			y++;
		x++;
	}
	if (z % 2 == 0 && z > 0)
		y = y - (z / 2);
	return (y);
}

static int	sizer(char const *s, char c)
{
	int		x;
	int		y;
	int		z;

	z = 0;
	x = 0;
	y = 0;
	if (s[x] == c && x == 0)
	{
		while (s[x] == c)
			x++;
	}
	if (s[x] == '\'')
		y = 1;
	while (s[x] && (s[x] != c || (s[x] == c && y == 1)))
	{
		x++;
		z++;
		if (s[x] == '\'')
			y = 0;
	}
	return (z);
}

static void	freeer(char **a, int y)
{
	int	x;

	x = 0;
	while (x <= y)
	{
		free(a[x]);
		a[x] = NULL;
		x++;
	}
	free(a);
	a = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		x;
	int		y;
	char	**a;

	a = malloc(sizeof(char *) * (liner(s, c) + 1));
	if (!a)
		return (0);
	x = 0;
	y = 0;
	while (*s)
	{
		if (*s && *s != c)
		{
			a[y] = ft_substr(s, 0, sizer(s, c));
			if (!a[y])
				return (freeer(a, y), NULL);
			s += sizer(s, c);
			y++;
		}
		else
			s++;
	}
	return (a[y] = NULL, a);
}

// int main()
// {
// 	char **a;

// 	a = ft_split("tr pi \' X\'", ' ');
// }
