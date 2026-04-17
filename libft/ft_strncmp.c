/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:10:42 by saouissi          #+#    #+#             */
/*   Updated: 2025/11/03 18:04:24 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;

	x = 0;
	while ((s1[x] || s2[x]) && x < n)
	{
		if (s1[x] != s2[x])
			return ((unsigned char )s1[x] - (unsigned char)s2[x]);
		x++;
	}
	return (0);
}
