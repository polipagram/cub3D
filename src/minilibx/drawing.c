/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:26:49 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/16 12:14:50 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_textured_line(t_projection proj,
							t_texture *tex, t_draw_3d *share3d, t_data *data)
{
	t_draw_textured_line	share;

	share.tex_x = (int)(share3d->wall_x * tex->width);
	share.step = (float)tex->height / proj.height;
	share.tex_pos = 0;
	share.y = proj.start;
	while (share.y < proj.start + proj.height && share.y < data->win_height)
	{
		share.tex_y = (int)share.tex_pos;
		share.color = get_texture_pixel(tex, share.tex_x, share.tex_y);
		if (share3d->x >= 0 && share3d->x < data->win_width
			&& share.y >= 0 && share.y < data->win_height)
			put_pixel(share3d->x, share.y, share.color, data);
		share.tex_pos += share.step;
		share.y++;
	}
}

void	draw_rectangle(int x, int y, int h, t_data *data)
{
	int				j;
	int				i;
	unsigned int	color;

	if (y == 0)
		color = data->file->c_rgb;
	else
		color = data->file->f_rgb;
	j = 0;
	while (j < h)
	{
		i = 0;
		while (i < 1)
		{
			put_pixel(i + x, j + y, color, data);
			i++;
		}
		j++;
	}
}

void	draw_ray(t_draw_rays *points, t_data *data)
{
	t_draw_ray	ray;

	ray.dx = points->x2 - points->x1;
	ray.dy = points->y2 - points->y1;
	if (abs(ray.dx) > abs(ray.dy))
		ray.steps = abs(ray.dx);
	else
		ray.steps = abs(ray.dy);
	if (ray.steps == 0)
		return ;
	ray.x_inc = ray.dx / (float)ray.steps;
	ray.y_inc = ray.dy / (float)ray.steps;
	ray.x = points->x1;
	ray.y = points->y1;
	ray.i = 0;
	while (ray.i <= ray.steps)
	{
		put_pixel(round(ray.x), round(ray.y), 0xFFF000, data);
		ray.x += ray.x_inc;
		ray.y += ray.y_inc;
		ray.i++;
	}
}

void	draw_square(int x, int y, t_data *game, int flag)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	if (flag)
		color = 0xFF0000;
	else
		color = 0xFFFF00;
	while (i < SQUERE - 1)
	{
		j = 0;
		while (j < SQUERE - 1)
		{
			put_pixel(x + j, y + i, color, game);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	char	**map;
	int		x;
	int		y;

	map = data->file->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * SQUERE, y * SQUERE, data, 0);
			x++;
		}
		y++;
	}
}
