/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:06:35 by tsargsya          #+#    #+#             */
/*   Updated: 2024/12/26 18:49:05 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static void	shift_buffer_after_nl(char *readbuffer);
static char	*strdup_till_nl(char *str);

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = 1;
	line = strdup_till_nl(buffer);
	if (!line)
		return (NULL);
	while (bytes > 0 && !ft_strchr(line, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (ft_bzero(buffer, BUFFER_SIZE), free(line), NULL);
		buffer[bytes] = '\0';
		line = ft_strjoin(line, buffer);
		if (!line)
			return (NULL);
	}
	if (!line[0] && bytes == 0)
		return (free(line), NULL);
	shift_buffer_after_nl(buffer);
	return (line);
}

static void	shift_buffer_after_nl(char *readbuffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (readbuffer[i] && readbuffer[i] != '\n')
		i++;
	if (readbuffer[i] == '\n')
		i++;
	while (readbuffer[i])
	{
		readbuffer[j] = readbuffer[i];
		i++;
		j++;
	}
	readbuffer[j] = '\0';
}

static char	*strdup_till_nl(char *str)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
