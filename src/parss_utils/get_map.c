/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:43:41 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/16 10:09:32 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	copy_line(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int	copy_map(char **content, char **map, int i)
{
	int	j;
	int	len;
	int	start;
	int	h;

	j = 0;
	start = i;
	len = len_to_new_line(content[start]);
	while (content[start])
	{
		h = len_to_new_line(content[start]);
		if (h >= len)
			len = h;
		start++;
	}
	while (content[i])
	{
		map[j] = malloc(len + 1);
		if (!map[j])
			return (printf("%s%s.\e[0m\n", RED, MALLOC_FAILED), 0);
		copy_line(map[j++], content[i++]);
	}
	map[j] = NULL;
	return (1);
}

int	store_map(t_data *map, char **content, int i)
{
	int	len;
	int	j;
	int	l;

	len = 0;
	j = i;
	while (content[j])
	{
		l = 0;
		skip_white_space(content[j], &l);
		if (!ft_isdigit(content[j][l]))
			return (printf("%s%s.\e[0m\n", YELLOW, SOMETHING_AFTER_MAP), 0);
		len++;
		j++;
	}
	len++;
	map->file->map = malloc(sizeof(char *) * len + 1);
	if (!map->file->map)
		return (0);
	if (!copy_map(content, map->file->map, i))
		return (0);
	return (1);
}
