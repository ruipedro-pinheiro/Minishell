/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:05:56 by saouissi          #+#    #+#             */
/*   Updated: 2026/03/09 16:19:19 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*filler(int fd, char *full)
{
	char			*buffer;
	char			*tmp;
	int				a;

	a = 1;
	if (!full)
		full = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!buffer)
		return (free(full), NULL);
	while (!ft_strchr(full, '\n') && a > 0)
	{
		a = read(fd, buffer, BUFFER_SIZE);
		if (a == -1)
			return (free(buffer), free(full), NULL);
		buffer[a] = 0;
		tmp = ft_strjoin(full, buffer);
		free(full);
		full = tmp;
	}
	free(buffer);
	return (full);
}

static char	*liner(char *buffer)
{
	int		x;
	char	*line;

	x = 0;
	if (!buffer[x])
		return (NULL);
	while (buffer[x] && buffer[x] != '\n')
		x++;
	line = malloc(x + 2);
	if (!line)
		return (NULL);
	x = 0;
	while (buffer[x] && buffer[x] != '\n')
	{
		line[x] = buffer[x];
		x++;
	}
	if (buffer[x] == '\n')
	{
		line[x] = '\n';
		x++;
	}
	line[x] = '\0';
	return (line);
}

static char	*nexter(char *buffer)
{
	int		x;
	int		y;
	char	*refuse;
	int		z;

	z = 0;
	y = 0;
	x = ft_strlen(buffer);
	while (buffer[y] && buffer[y] != '\n')
		y++;
	if (x != y)
	{
		refuse = malloc(x - y + 1);
		if (!refuse)
			return (NULL);
	}
	else
		return (NULL);
	y++;
	while (y < x)
		refuse[z++] = buffer[y++];
	refuse[z] = 0;
	return (refuse);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;
	char		*refuse;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = filler(fd, buffer);
	if (!buffer)
		return (NULL);
	line = liner(buffer);
	refuse = nexter(buffer);
	if (buffer)
		free(buffer);
	buffer = refuse;
	return (line);
}
