/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouarfa <kbouarfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:49:57 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/09 18:30:14 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_texture	*load_texture(t_data *data, char *path)
{
	t_texture	*tex;

	tex = malloc(sizeof(t_texture));
	if (!tex)
		return (NULL);
	if (path)
		tex->img = mlx_xpm_file_to_image(data->mlx,
				path, &tex->width, &tex->height);
	else
		tex->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!tex->img)
		return (free(tex), NULL);
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_len, &tex->endian);
	return (tex);
}

int	load_textures(t_data *data)
{
	data->frame = load_texture(data, NULL);
	data->tex_no = load_texture(data, data->file->north);
	data->tex_so = load_texture(data, data->file->south);
	data->tex_we = load_texture(data, data->file->west);
	data->tex_ea = load_texture(data, data->file->east);
	if (!data->tex_no || !data->tex_so || !data->tex_we || !data->tex_ea)
		return (printf("Failed to load textures\n"), 0);
	return (1);
}

unsigned int	get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

t_texture	*get_wall_texture(t_data *data, int type_of_inter)
{
	if (type_of_inter == NO)
		return (data->tex_no);
	else if (type_of_inter == SO)
		return (data->tex_so);
	else if (type_of_inter == WE)
		return (data->tex_we);
	else
		return (data->tex_ea);
}

float	get_wall_x(t_ray_hit hit)
{
	float	wall_x;

	if (hit.type == NO || hit.type == SO)
		wall_x = hit.hit_x / SQUERE;
	else
		wall_x = hit.hit_y / SQUERE;
	wall_x = wall_x - floor(wall_x);
	return (wall_x);
}
