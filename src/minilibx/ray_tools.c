/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:56:57 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/16 13:05:34 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	normalize_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int	check_facing_up(float angle)
{
	return (angle > M_PI && angle < 2 * M_PI);
}

int	check_facing_right(float angle)
{
	return (angle < M_PI / 2 || angle > 1.5 * M_PI);
}

float	calculate_distance(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	next_point(float angle, float len, t_draw_rays *ray)
{
	ray->x2 = ray->x1 + (int)(cos(angle) * len);
	ray->y2 = ray->y1 + (int)(sin(angle) * len);
}
