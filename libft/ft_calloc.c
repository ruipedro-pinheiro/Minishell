/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:12:03 by saouissi          #+#    #+#             */
/*   Updated: 2026/03/09 16:22:52 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*a;

	if (nmemb * size > __SIZE_MAX__)
		return (0);
	a = malloc(nmemb * size);
	if (!a)
		return (0);
	ft_bzero(a, nmemb * size);
	return (a);
}
