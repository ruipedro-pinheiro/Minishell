/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:16:00 by saouissi          #+#    #+#             */
/*   Updated: 2026/03/09 16:21:37 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	x;
	char			*a;

	x = 0;
	a = malloc(ft_strlen(s) + 1);
	if (!a)
		return (0);
	while (s[x])
	{
		a[x] = f(x, s[x]);
		x++;
	}
	a[x] = 0;
	return (a);
}
