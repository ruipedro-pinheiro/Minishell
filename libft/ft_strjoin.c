/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:04:52 by saouissi          #+#    #+#             */
/*   Updated: 2026/03/09 16:21:48 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			x;
	int			y;
	int			z;
	char		*a;

	z = 0;
	y = ft_strlen(s2);
	x = ft_strlen(s1);
	a = malloc((x + y + 1) * sizeof(char));
	if (!a)
		return (0);
	y = 0;
	while (s1[z])
	{
		a[z] = s1[z];
		z++;
	}
	while (s2[y])
	{
		a[z] = s2[y];
		z++;
		y++;
	}
	a[z] = 0;
	return (a);
}
