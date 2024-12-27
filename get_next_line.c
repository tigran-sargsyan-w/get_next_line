/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:21:57 by tsargsya          #+#    #+#             */
/*   Updated: 2024/12/27 16:03:00 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static void	shift_buffer_after_nl(char *readbuffer);
static char	*strdup_till_nl(char *str);
static char	*read_and_join(int fd, char **buffers, char *line);
static char	*handle_empty_line(char **buffers, int fd, char *line);

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffers[MAX_FD];

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffers[fd])
	{
		buffers[fd] = malloc(BUFFER_SIZE + 1);
		if (!buffers[fd])
			return (NULL);
		buffers[fd][0] = '\0';
	}
	line = strdup_till_nl(buffers[fd]);
	if (!line)
		return (NULL);
	line = read_and_join(fd, buffers, line);
	if (!line)
		return (NULL);
	line = handle_empty_line(buffers, fd, line);
	if (!line)
		return (NULL);
	shift_buffer_after_nl(buffers[fd]);
	return (line);
}

static char	*read_and_join(int fd, char **buffers, char *line)
{
	int	bytes;

	bytes = 1;
	while (bytes > 0 && !ft_strchr(line, '\n'))
	{
		bytes = read(fd, buffers[fd], BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffers[fd]);
			buffers[fd] = NULL;
			free(line);
			return (NULL);
		}
		buffers[fd][bytes] = '\0';
		line = ft_strjoin(line, buffers[fd]);
		if (!line)
		{
			free(buffers[fd]);
			buffers[fd] = NULL;
			return (NULL);
		}
	}
	return (line);
}

static char	*handle_empty_line(char **buffers, int fd, char *line)
{
	if (!line[0])
	{
		free(buffers[fd]);
		buffers[fd] = NULL;
		free(line);
		return (NULL);
	}
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
