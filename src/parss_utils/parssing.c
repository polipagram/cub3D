/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:45:17 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/14 16:20:04 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_textures(t_data *map, char **content, int i, int j)
{
	if (ft_isprint(content[i][j]) && !ft_isprint(content[i][j + 1]))
	{
		if (!store_colors(map, content[i]))
			return (0);
	}
	else
	{
		if (!store_textures(map, content[i]))
			return (0);
	}
	return (1);
}

int	get_map(t_data *map, char **content, int i)
{
	if (check_top_bottom(content[i]))
	{
		if (!store_map(map, content, i))
			return (0);
		return (1);
	}
	return (0);
}

int	check_file_content(t_file *file)
{
	if (!file->c_color || !file->f_color)
		return (printf("%s%s.\e[0m\n", YELLOW, MISSING_COLOR), 0);
	if (!file->east || !file->north
		|| !file->south || !file->west)
		return (printf("%s%s.\e[0m\n", PINK, MISSING_TEXTURE), 0);
	return (1);
}

int	split_content(t_data *map)
{
	int		i;
	int		j;
	char	**content;

	i = 0;
	content = map->file->content;
	while (content[i])
	{
		j = 0;
		skip_white_space(content[i], &j);
		if (ft_isprint(content[i][j]) && !ft_isdigit(content[i][j]))
		{
			if (!get_textures(map, content, i, j))
				return (0);
		}
		else if (ft_isdigit(content[i][j]))
		{
			if (!check_file_content(map->file))
				return (0);
			return (get_map(map, content, i));
		}
		i++;
	}
	return (1);
}

int	parssing(t_data *map, char *path)
{
	if (!allocat_data_members(map, path))
		return (0);
	map->player->x = -1;
	map->player->y = -1;
	if (!store_content(map))
		return (0);
	if (!split_content(map))
		return (0);
	if (!check_file_content(map->file))
		return (0);
	if (!map->file->map)
		return (printf("%s%s.\e[0m\n", PINK, INVALID_MAP), 0);
	if (!check_map(map->file->map, map))
		return (0);
	if (map->player->x == -1 || map->player->y == -1)
		return (printf("%s%s.\e[0m\n", YELLOW, MISSING_DIR_CHAR), 0);
	return (1);
}
