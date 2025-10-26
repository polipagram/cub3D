/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:52:15 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/09 09:28:09 by mbounoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_images(t_data *data)
{
	if (data)
	{
		if (data->tex_ea->img)
			mlx_destroy_image(data->mlx, data->tex_ea->img);
		if (data->tex_so->img)
			mlx_destroy_image(data->mlx, data->tex_so->img);
		if (data->tex_no->img)
			mlx_destroy_image(data->mlx, data->tex_no->img);
		if (data->tex_we->img)
			mlx_destroy_image(data->mlx, data->tex_we->img);
		if (data->frame->img)
			mlx_destroy_image(data->mlx, data->frame->img);
	}
}

void	free_textures(t_data *data)
{
	if (data)
	{
		if (data->tex_ea)
			free(data->tex_ea);
		if (data->tex_so)
			free(data->tex_so);
		if (data->tex_no)
			free(data->tex_no);
		if (data->tex_we)
			free(data->tex_we);
		if (data->frame)
			free(data->frame);
	}
}

int	clean_exit(t_data *data)
{
	free_file(data->file);
	free(data->player);
	free_images(data);
	free_textures(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	exit(0);
}
