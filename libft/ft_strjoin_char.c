/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:38:58 by rpinheir          #+#    #+#             */
/*   Updated: 2026/05/13 14:39:57 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char *s, char c)
{
	char	tmp[2];
	char	*result;

	tmp[0] = c;
	tmp[1] = '\0';
	result = ft_strjoin(s, tmp);
	free(s);
	return (result);
}
