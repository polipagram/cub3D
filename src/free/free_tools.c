/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 09:26:22 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/16 09:19:39 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_parssing(t_data *data)
{
	free_file(data->file);
	free(data->player);
	free(data);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	clear_image(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->file->hight * SQUERE)
	{
		x = 0;
		while (x < data->file->width * SQUERE)
		{
			put_pixel(x, y, 0, data);
			x++;
		}
		y++;
	}
}

void	free_file(t_file *file)
{
	if (file->c_color)
		free(file->c_color);
	if (file->f_color)
		free(file->f_color);
	if (file->map)
		free_tab(file->map);
	if (file->content)
		free_tab(file->content);
	if (file->north)
		free(file->north);
	if (file->south)
		free(file->south);
	if (file->west)
		free(file->west);
	if (file->east)
		free(file->east);
	if (file->path)
		free(file->path);
	free(file);
}

void	print_exit(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
