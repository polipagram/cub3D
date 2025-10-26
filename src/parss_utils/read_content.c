/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:19:47 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/14 11:14:57 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	count_lines(t_data *map)
{
	int		fd;
	char	*line;
	int		len;

	fd = open(map->file->path, O_RDONLY);
	if (fd == -1)
		return (-1);
	len = 0;
	line = get_next_line(fd);
	if (!line)
		return (-1);
	while (line != NULL)
	{
		len++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (len + 1);
}

void	free_tab_to_index(char **tab, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(tab[j]);
		j++;
	}
	free(tab);
}

char	**read_content(int fd, char **content)
{
	char	*line;
	int		len;
	int		i;

	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		len = len_to_new_line(line);
		content[i] = malloc(sizeof(char) * len + 1);
		if (!content[i])
			return (printf("%s%s.\e[0m\n", RED, MALLOC_FAILED),
				free_tab_to_index(content, i), NULL);
		content[i] = ft_memmove(content[i], line, len);
		content[i][len] = '\0';
		i++;
		free(line);
		line = get_next_line(fd);
	}
	content[i] = NULL;
	return (content);
}

int	store_content(t_data *map)
{
	int		len;
	int		fd;
	char	**content;

	len = count_lines(map);
	if (len == -1)
		return (0);
	content = malloc(sizeof(char *) * len + 1);
	if (!content)
		return (printf("%s%s.\e[0m\n", RED, MALLOC_FAILED), 0);
	fd = open(map->file->path, O_RDONLY);
	if (fd == -1)
		return (free(content), 0);
	map->file->content = read_content(fd, content);
	if (!map->file->content)
		return (free(content), close(fd), 0);
	close(fd);
	return (1);
}
