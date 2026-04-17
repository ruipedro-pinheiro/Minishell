/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:10:18 by saouissi          #+#    #+#             */
/*   Updated: 2025/11/03 18:04:54 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	x;

	x = 0;
	while (c > 127)
		c -= 256;
	while (s[x] != 0)
		x++;
	while (x != 0)
	{
		if (s[x] == c)
			return ((char *)&s[x]);
		x--;
	}
	if (x == 0)
	{
		if (s[x] == c)
			return ((char *)&s[x]);
	}
	return (0);
}
