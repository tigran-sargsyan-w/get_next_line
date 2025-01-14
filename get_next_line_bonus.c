/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:21:57 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/11 20:01:46 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffers[MAX_FD][BUFFER_SIZE + 1];

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	line = strdup_till_nl(buffers[fd]);
	if (!line)
	{
		buffers[fd][0] = '\0';
		return (NULL);
	}
	line = read_and_join(fd, buffers[fd], line);
	if (!line)
	{
		buffers[fd][0] = '\0';
		return (NULL);
	}
	line = handle_empty_line(buffers[fd], line);
	if (!line)
	{
		buffers[fd][0] = '\0';
		return (NULL);
	}
	shift_buffer_after_nl(buffers[fd]);
	return (line);
}

char	*strdup_till_nl(char *str)
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

char	*read_and_join(int fd, char *buffers, char *line)
{
	int	bytes;

	bytes = 1;
	while (bytes > 0 && !ft_strchr(line, '\n'))
	{
		bytes = read(fd, buffers, BUFFER_SIZE);
		if (bytes == -1)
		{
			buffers[0] = '\0';
			free(line);
			return (NULL);
		}
		buffers[bytes] = '\0';
		line = strjoin_till_nl(line, buffers);
		if (!line)
		{
			buffers[0] = '\0';
			return (NULL);
		}
	}
	return (line);
}

char	*handle_empty_line(char *buffers, char *line)
{
	if (!line[0])
	{
		buffers[0] = '\0';
		free(line);
		return (NULL);
	}
	return (line);
}

void	shift_buffer_after_nl(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i])
	{
		buffer[j] = buffer[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
}
