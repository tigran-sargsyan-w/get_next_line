/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:13:10 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/11 19:30:03 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

int	main(void)
{
	char	*line;
	int		end_of_file[4] = {0, 0, 0, 0};
	int		files_remaining;

	int fd1, fd2, fd3, fd4;
	files_remaining = 4;
	fd1 = open("tests/file1.txt", O_RDONLY);
	fd2 = open("tests/file2.txt", O_RDONLY);
	fd3 = open("tests/file3.txt", O_RDONLY);
	fd4 = open("tests/file4.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1)
	{
		perror("Error opening file");
		return (0);
	}
	while (files_remaining > 0)
	{
		if (!end_of_file[0])
		{
			// fd1 = 42;
			// close(fd1);
			printf("%d\n", fd1);
			line = get_next_line(fd1);
			printf("line: %s\n", line);
			if (line)
			{
				printf(RED "file1: %s" RESET, line);
				free(line);
			}
			else
			{
				end_of_file[0] = 1;
				files_remaining--;
			}
		}
		if (!end_of_file[1])
		{
			line = get_next_line(fd2);
			if (line)
			{
				printf(GREEN "file2: %s" RESET, line);
				free(line);
			}
			else
			{
				end_of_file[1] = 1;
				files_remaining--;
			}
		}
		if (!end_of_file[2])
		{
			line = get_next_line(fd3);
			if (line)
			{
				printf(YELLOW "file3: %s" RESET, line);
				free(line);
			}
			else
			{
				end_of_file[2] = 1;
				files_remaining--;
			}
		}
		if (!end_of_file[3])
		{
			line = get_next_line(fd4);
			if (line)
			{
				printf(BLUE "file4: %s" RESET, line);
				free(line);
			}
			else
			{
				end_of_file[3] = 1;
				files_remaining--;
			}
		}
	}
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	return (0);
}
