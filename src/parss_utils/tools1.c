/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:30:55 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/08 10:40:18 by mbounoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	allocat_data_members(t_data *map, char *path)
{
	int	len;

	len = ft_strlen(path);
	map->file = malloc(sizeof(t_file));
	if (!map->file)
		return (0);
	ft_memset(map->file, 0, sizeof(t_file));
	map->player = malloc(sizeof(t_player));
	if (!map->player)
		return (free(map->file), 0);
	map->file->path = malloc(len + 1);
	if (!map->file->path)
		return (free(map->player), free(map->file), 0);
	ft_memmove(map->file->path, path, len);
	map->file->path[len] = '\0';
	return (1);
}

void	free_array(void *array, int type)
{
	int		i;
	char	**tab_c;
	int		**tab_i;

	i = 0;
	if (type == 0)
	{
		tab_c = (char **)array;
		while (tab_c[i])
			free(tab_c[i++]);
		free(tab_c);
	}
	else if (type == 1)
	{
		tab_i = (int **)array;
		while (tab_i[i])
			free(tab_i[i++]);
		free(tab_i);
	}
}
