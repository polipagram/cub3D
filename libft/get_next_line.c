/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:06:45 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/14 16:21:21 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/cub3d.h"

char	*join_old_new(char *old, char *new)
{
	char	*joind;

	joind = ft_strjoin(old, new);
	free(old);
	return (joind);
}

char	*filter_line(char **buffer)
{
	char	*line;
	char	*after_newline;
	char	*temp;
	size_t	len;

	after_newline = ft_strchr(*buffer, '\n');
	if (!after_newline)
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
		return (line);
	}
	len = after_newline - *buffer + 1;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *buffer, len + 1);
	temp = ft_strdup(after_newline + 1);
	free(*buffer);
	*buffer = temp;
	return (line);
}

char	*read_line(int fd, char *buffer)
{
	char	*temp;
	ssize_t	bytes_read;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while (!buffer || !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(temp);
			return (printf("%s%s.\n", YELLOW, strerror(errno)), NULL);
		}
		if (bytes_read == 0)
			break ;
		temp[bytes_read] = '\0';
		buffer = join_old_new(buffer, temp);
	}
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (filter_line(&buffer));
}
