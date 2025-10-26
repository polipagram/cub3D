/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 08:50:06 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/16 17:45:26 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_horizontal_intersection(t_data *data,
									float ray_angle, float *x, float *y)
{
	if (check_facing_up(ray_angle))
		*y = floor(data->player->y / SQUERE) * SQUERE - 0.001;
	else
		*y = floor(data->player->y / SQUERE) * SQUERE + SQUERE;
	*x = data->player->x + (*y - data->player->y) / tan(ray_angle);
}

void	get_vertical_intersection(t_data *data,
								float ray_angle, float *x, float *y)
{
	if (check_facing_right(ray_angle))
		*x = floor(data->player->x / SQUERE) * SQUERE + SQUERE;
	else
		*x = floor(data->player->x / SQUERE) * SQUERE - 0.001;
	*y = data->player->y + (*x - data->player->x) * tan(ray_angle);
}
