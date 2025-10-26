/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:30:23 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/16 09:38:27 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	convert_color_to_hex(int *colors)
{
	unsigned int	result;

	result = 0;
	result += (colors[0]) << 16;
	result += (colors[1]) << 8;
	result += (colors[2]);
	return (result);
}

int	check_digits(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if (!ft_isdigit(num[i]) && ft_isprint(num[i]))
			return (printf("%s%s\e[0m.\n", PINK, HAS_CHAR), 0);
		i++;
	}
	return (1);
}

int	*split_color(char *line)
{
	char	**color;
	int		*rgb;
	int		i;

	i = 0;
	color = ft_split(line, ',');
	if (array_len(color) != 3)
		return (printf("%s%s.\e[0m\n", YELLOW, MORE_THAN_FOUR),
			free_array(color, 0), NULL);
	rgb = malloc(sizeof(int) * 4);
	if (!rgb)
		return (printf("%s%s.\e[0m\n", RED, MALLOC_FAILED),
			free_array(color, 0), NULL);
	while (color[i])
	{
		rgb[i] = ft_atoi(color[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (printf("%s%s.\e[0m\n", YELLOW, COLOR_RANGE_OUT), free(rgb),
				free_array(color, 0), NULL);
		if (!check_digits(color[i]))
			return (free(rgb), free_array(color, 0), NULL);
		i++;
	}
	rgb[i] = -1;
	return (free_array(color, 0), rgb);
}

int	store_colors(t_data *map, char *line)
{
	int		*colors;
	char	c;
	int		i;

	i = 0;
	skip_white_space(line, &i);
	c = line[i];
	if (c != 'F' && c != 'C')
		return (printf("%s%s.\e[0m\n", YELLOW, INVALID_LINE), 0);
	colors = split_color(&line[i + 1]);
	if (!colors)
		return (0);
	if (c == 'F' && !map->file->f_color)
	{
		map->file->f_color = colors;
		map->file->f_rgb = convert_color_to_hex(colors);
	}
	else if (c == 'C' && !map->file->c_color)
	{
		map->file->c_color = colors;
		map->file->c_rgb = convert_color_to_hex(colors);
	}
	else
		return (printf("%s%s.\e[0m\n", YELLOW, INVALID_LINE), free(colors), 0);
	return (1);
}
