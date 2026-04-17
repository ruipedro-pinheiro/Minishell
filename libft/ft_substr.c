/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:45:27 by saouissi          #+#    #+#             */
/*   Updated: 2026/03/09 16:21:20 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	size_t	x;

	x = 0;
	if (start >= ft_strlen(s))
	{
		a = malloc(sizeof(char) * 1);
		if (!a)
			return (0);
		a[0] = 0;
		return (a);
	}
	else if (ft_strlen(s + start) < len)
		a = malloc(sizeof(char) * (ft_strlen(s + start) + 1));
	else
		a = malloc(sizeof(char) * (len + 1));
	if (!a)
		return (0);
	while (x < len && s[(size_t)start + x])
	{
		a[x] = s[(size_t)start + x];
		x++;
	}
	a[x] = 0;
	return (a);
}
