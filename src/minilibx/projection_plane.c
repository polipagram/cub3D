/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:54:42 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/09 09:40:35 by mbounoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calc_projection_height(t_projection *proj,
							float len, float ray_angle, t_data *data)
{
	proj->perp_dist = len * cos(ray_angle - data->player->angle);
	proj->dist = (data->win_width / 2) / tan(data->player->fov / 2.0f);
	proj->height = (SQUERE / proj->perp_dist) * proj->dist;
	proj->start = (data->win_height / 2) - (proj->height / 2);
}

void	draw_one_projection(t_draw_3d *share,
							t_projection proj, t_data *data, t_texture *tex)
{
	int	j;
	int	floor_height;
	int	ceil_height;
	int	floor_y;

	floor_height = data->win_height - (proj.height + proj.start);
	floor_y = proj.start + proj.height;
	ceil_height = proj.start;
	j = 0;
	while (j < RES && (share->i * RES + j) < data->win_width)
	{
		share->x = share->i * RES + j;
		draw_textured_line(proj, tex, share, data);
		draw_rectangle(share->x, floor_y, floor_height, data);
		draw_rectangle(share->x, 0, ceil_height, data);
		j++;
	}
}
