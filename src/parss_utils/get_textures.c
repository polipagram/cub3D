/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:26:55 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/16 09:53:40 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	skip_white_space(char *str, int *i)
{
	while (str[*i] && ((!ft_isprint((unsigned char)str[*i])) || str[*i] == ' '))
		(*i)++;
}

int	len_to_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*get_texture(char *line)
{
	int		i;
	int		fd;
	char	*path;
	int		len;

	i = 0;
	skip_white_space(line, &i);
	len = len_to_new_line(&line[i]);
	path = malloc(sizeof(char) * len + 1);
	if (!path)
		return (printf("%s%s.\e[0m\n", RED, MALLOC_FAILED), NULL);
	ft_memmove(path, &line[i], len);
	path[len] = '\0';
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (printf("%s%s.\e[0m\n", RED, INVALID_TEXTURE),
			free(path), NULL);
	return (path);
}

int	store_textures(t_data *map, char *line)
{
	char	*texture;
	int		i;

	i = 0;
	skip_white_space(line, &i);
	texture = get_texture(&line[i + 2]);
	if (!texture)
		return (0);
	if (!ft_strncmp("NO ", &line[i], 3) && !map->file->north)
		map->file->north = texture;
	else if (!ft_strncmp("SO ", &line[i], 3) && !map->file->south)
		map->file->south = texture;
	else if (!ft_strncmp("WE ", &line[i], 3) && !map->file->west)
		map->file->west = texture;
	else if (!ft_strncmp("EA ", &line[i], 3) && !map->file->east)
		map->file->east = texture;
	else
		return (printf("%s%s.\e[0m\n", RED, INVALID_TEXTURE), free(texture), 0);
	return (1);
}
