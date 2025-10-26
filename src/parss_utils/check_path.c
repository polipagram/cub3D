/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:27:59 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/14 11:13:26 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_cub(char *path)
{
	size_t	i;

	i = ft_strlen(path);
	if (ft_strcmp(".cub", &path[i - 4]))
		return (printf("%s%s.\e[0m\n", PINK, INVALID_EXT), 0);
	return (1);
}

int	check_xpm(char *path)
{
	size_t	i;

	i = ft_strlen(path);
	if (ft_strcmp(".xpm", &path[i - 4]))
		return (printf("%s%s.\e[0m\n", BLUE, INVALID_EXT), 0);
	return (1);
}

int	check_extension(char *path, int flag)
{
	if (flag == 1)
		return (check_cub(path));
	else
		return (check_xpm(path));
}

int	check_wall(int x, int y, t_data *data)
{
	if (x < 0 || y < 0 || x >= data->file->width || y >= data->file->hight)
		return (1);
	return (data->file->map[y][x] == '1');
}

int	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (printf("%s%s.\e[0m\n", PINK, strerror(errno)), 0);
	close(fd);
	if (!check_extension(path, CUB))
		return (0);
	return (1);
}
