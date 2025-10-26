/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouarfa <kbouarfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:53:14 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/17 10:34:44 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

int	valid_char(char c)
{
	if (ft_isprint(c))
		if (!ft_strchr("01ESWNO", c))
			return (printf("%s%s '%c'.\e[0m\n", RED, INVALID_CHAR, c), 0);
	return (1);
}

int	check_top_bottom(char *row)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (row[i] != '1')
			if (ft_isprint(row[i]))
				return (printf("%s%s.\e[0m\n", RED, HOLE_IN_MAP), 0);
		i++;
	}
	return (1);
}

void	player_angle(t_data *data, char **map, int i, int j)
{
	if (map[i][j] == 'N')
		data->player->angle = 90 * M_PI / 180;
	else if (map[i][j] == 'S')
		data->player->angle = 270 * M_PI / 180;
	else if (map[i][j] == 'W')
		data->player->angle = 180 * M_PI / 180;
	else
		data->player->angle = 0 * M_PI / 180;
}

int	check_char_position(t_data *data, char **map, t_check_map *share)
{
	if (ft_strchr("ESWN", map[share->i][share->j]))
	{
		if (!share->flag)
			return (printf("%s%s.\e[0m\n", YELLOW, DOUBLE_DIR_CHAR), 0);
		share->flag = 0;
		data->player->y = share->i * SQUERE;
		data->player->x = share->j * SQUERE;
		player_angle(data, map, share->i, share->j);
	}
	if (!valid_char(map[share->i][share->j]))
		return (0);
	if (map[share->i][share->j] != '1' && ft_isprint(map[share->i][share->j]))
	{
		if ((!map[share->i][share->j + 1]
			|| !ft_isprint(map[share->i][share->j + 1]))
			|| (!map[share->i][share->j - 1]
			|| !ft_isprint(map[share->i][share->j - 1]))
			|| (!map[share->i + 1][share->j]
			|| !ft_isprint(map[share->i + 1][share->j]))
			|| (!map[share->i - 1][share->j]
			|| !ft_isprint(map[share->i - 1][share->j])))
			return (printf("%s%s.\e[0m\n", RED, HOLE_IN_MAP), 0);
	}
	return (1);
}

int	check_map(char **map, t_data *data)
{
	t_check_map	share;

	share.i = 0;
	share.flag = 1;
	share.len = ft_strlen(map[share.i]);
	while (map[share.i])
	{
		share.j = 0;
		while (map[share.i][share.j])
		{
			if (!check_char_position(data, map, &share))
				return (0);
			share.j++;
		}
		share.i++;
	}
	data->file->width = share.len;
	data->file->hight = share.i;
	return (1);
}
