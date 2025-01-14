/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:22:28 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/11 20:01:51 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == 0)
		return ((char *)s);
	return (NULL);
}

char	*strjoin_till_nl(char *line, char *buffer)
{
	char	*str;
	size_t	size;
	size_t	i;
	size_t	j;

	i = 0;
	if (!line || !buffer)
		return (NULL);
	j = ft_strlen(line);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	size = i + j;
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (free(line), NULL);
	ft_memcpy(str, line, j);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		str[j++] = buffer[i++];
	if (buffer[i] == '\n')
		str[j++] = buffer[i++];
	str[j] = '\0';
	return (free(line), str);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (dest);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
