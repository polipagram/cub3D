/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:56:44 by kbouarfa          #+#    #+#             */
/*   Updated: 2025/10/17 10:38:55 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->fov = 60 * M_PI / 180;
	player->left_right = 0;
	player->top_bottom = 0;
	player->turn_direction = 0;
	player->move_speed = 5;
	player->rot_speed = 1 * M_PI / 180;
}

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		clean_exit(data);
	if (key == W || key == UP)
		data->player->top_bottom = 1;
	if (key == S || key == DOWN)
		data->player->top_bottom = -1;
	if (key == A)
		data->player->left_right = -1;
	if (key == D)
		data->player->left_right = 1;
	if (key == RIGHT)
		data->player->turn_direction = 1;
	if (key == LEFT)
		data->player->turn_direction = -1;
	return (1);
}

int	key_release(int key, t_player *player)
{
	if (key == W || key == S || key == UP || key == DOWN)
		player->top_bottom = 0;
	if (key == A || key == D)
		player->left_right = 0;
	if (key == LEFT || key == RIGHT)
		player->turn_direction = 0;
	return (1);
}

void	move_player(t_player *player, t_data *data)
{
	float	move_step;
	float	new_h_x;
	float	new_h_y;

	player->angle += player->turn_direction * player->rot_speed;
	player->angle = normalize_angle(player->angle);
	move_step = player->top_bottom * player->move_speed;
	new_h_x = player->x + cos(player->angle) * move_step;
	new_h_y = player->y + sin(player->angle) * move_step;
	if (!check_wall((new_h_x / SQUERE), (new_h_y / SQUERE), data))
	{
		player->x = new_h_x;
		player->y = new_h_y;
	}
	move_step = player->left_right * player->move_speed;
	new_h_x = player->x + cos(player->angle + M_PI / 2) * move_step;
	new_h_y = player->y + sin(player->angle + M_PI / 2) * move_step;
	if (!check_wall((new_h_x / SQUERE), (new_h_y / SQUERE), data))
	{
		player->x = new_h_x;
		player->y = new_h_y;
	}
}
