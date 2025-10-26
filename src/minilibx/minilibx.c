/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:54:03 by kbouarfa          #+#    #+#             */
/*   Updated: 2025/10/17 10:39:30 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_pixel(int x, int y, unsigned int color, t_data *data)
{
	int	index;

	if (x >= data->win_width || x < 0 || y >= data->win_height || y < 0)
		return ;
	index = (y * data->frame->line_len) + (x * data->frame->bpp / 8);
	data->frame->addr[index] = color & 255;
	data->frame->addr[index + 1] = (color >> 8) & 255;
	data->frame->addr[index + 2] = (color >> 16) & 255;
}

void	draw_3d(t_data *data)
{
	float			ray_angle;
	t_texture		*tex;
	t_ray_hit		hit;
	t_projection	proj;
	t_draw_3d		share;

	share.i = 0;
	ray_angle = normalize_angle(data->player->angle - data->player->fov / 2);
	while (share.i < data->num_rays)
	{
		cast_ray(data, ray_angle, &hit);
		calc_projection_height(&proj, hit.len, ray_angle, data);
		share.wall_x = get_wall_x(hit);
		tex = get_wall_texture(data, hit.type);
		draw_one_projection(&share, proj, data, tex);
		ray_angle += data->player->fov / data->num_rays;
		ray_angle = normalize_angle(ray_angle);
		share.i++;
	}
}

int	draw_loop(t_data *data)
{
	move_player(data->player, data);
	clear_image(data);
	if (THREE_D)
		draw_3d(data);
	else
	{
		draw_square(data->player->x, data->player->y, data, 1);
		draw_map(data);
		draw_rays(data);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->frame->img, 0, 0);
	return (1);
}

int	init_data(t_data *data)
{
	data->win_width = data->file->width * SQUERE;
	data->win_height = data->file->hight * SQUERE;
	data->num_rays = data->win_width / RES;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (printf("mlx_init failed\n"), 0);
	data->win = mlx_new_window(data->mlx, data->win_width,
			data->win_height, "The Maze Runner");
	if (!data->win)
		return (printf("mlx_new_window failed\n"), 0);
	if (!load_textures(data))
		return (0);
	return (1);
}

int	minilibx(t_data *data)
{
	if (!init_data(data))
		return (0);
	init_player(data->player);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data->player);
	mlx_hook(data->win, 17, 0, clean_exit, data);
	mlx_loop_hook(data->mlx, draw_loop, data);
	mlx_loop(data->mlx);
	return (1);
}
