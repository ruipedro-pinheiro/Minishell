/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:09:56 by saouissi          #+#    #+#             */
/*   Updated: 2025/11/03 18:04:01 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int	x;

	x = 0;
	while (c > 127)
		c -= 256;
	while (s[x] != '\0' && s[x] != c)
		x++;
	if (s[x] == c)
		return ((char *)&s[x]);
	return (0);
}
