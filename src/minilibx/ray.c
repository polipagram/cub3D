/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouarfa <kbouarfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:53:58 by kbouarfa          #+#    #+#             */
/*   Updated: 2025/10/16 13:03:04 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_rays(t_data *data)
{
	t_ray_hit	hit;
	t_draw_rays	points;
	float		ray_angle;
	int			i;

	points.x1 = data->player->x;
	points.y1 = data->player->y;
	i = 0;
	ray_angle = normalize_angle(data->player->angle - data->player->fov / 2);
	while (i < data->num_rays)
	{
		cast_ray(data, ray_angle, &hit);
		next_point(ray_angle, hit.len, &points);
		draw_ray(&points, data);
		ray_angle += data->player->fov / data->num_rays;
		ray_angle = normalize_angle(ray_angle);
		i++;
	}
}

void	get_horizontal_wall(t_data *data,
							int *next_x, int *next_y, float ray_angle)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;

	get_horizontal_intersection(data, ray_angle, &x, &y);
	if (check_facing_up(ray_angle))
		y_step = -SQUERE;
	else
		y_step = SQUERE;
	x_step = y_step / tan(ray_angle);
	while (True)
	{
		if (check_wall(floor(x / SQUERE), floor(y / SQUERE), data))
			break ;
		x += x_step;
		y += y_step;
	}
	*next_x = (int)x;
	*next_y = (int)y;
}

void	get_vertical_wall(t_data *data,
						int *next_x, int *next_y, float ray_angle)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;

	get_vertical_intersection(data, ray_angle, &x, &y);
	if (check_facing_right(ray_angle))
		x_step = SQUERE;
	else
		x_step = -SQUERE;
	y_step = x_step * tan(ray_angle);
	while (True)
	{
		if (check_wall(floor(x / SQUERE), floor(y / SQUERE), data))
			break ;
		x += x_step;
		y += y_step;
	}
	*next_x = (int)x;
	*next_y = (int)y;
}

void	get_ray_info(float ray_angle, t_ray_hit *ray, t_cast_ray share)
{
	if (share.v_dist <= share.h_dist)
	{
		ray->len = share.v_dist;
		if (check_facing_right(ray_angle))
			ray->type = EA;
		else
			ray->type = WE;
		ray->hit_x = share.v_x;
		ray->hit_y = share.v_y;
	}
	else
	{
		ray->len = share.h_dist;
		if (check_facing_up(ray_angle))
			ray->type = NO;
		else
			ray->type = SO;
		ray->hit_x = share.h_x;
		ray->hit_y = share.h_y;
	}
}

void	cast_ray(t_data *data, float ray_angle, t_ray_hit *ray)
{
	t_cast_ray	share;

	get_horizontal_wall(data, &share.h_x, &share.h_y, ray_angle);
	get_vertical_wall(data, &share.v_x, &share.v_y, ray_angle);
	share.h_dist = calculate_distance(data->player->x,
			data->player->y, share.h_x, share.h_y);
	share.v_dist = calculate_distance(data->player->x,
			data->player->y, share.v_x, share.v_y);
	get_ray_info(ray_angle, ray, share);
}
