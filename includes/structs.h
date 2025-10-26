/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:26:58 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/13 09:36:32 by mbounoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_projection
{
	float	height;
	float	perp_dist;
	float	dist;
	int		start;
}	t_projection;

typedef struct s_texture {
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_ray_hit {
	float	len;
	float	hit_x;
	float	hit_y;
	int		type;
}	t_ray_hit;

typedef struct s_player
{
	float	x;
	float	y;
	int		turn_direction;
	int		top_bottom;
	int		left_right;
	float	angle;
	float	fov;
	float	move_speed;
	double	rot_speed;
}		t_player;

typedef struct s_file
{
	char			*path;
	char			**content;
	char			**map;
	int				hight;
	int				width;
	int				*f_color;
	int				*c_color;
	unsigned int	f_rgb;
	unsigned int	c_rgb;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
}	t_file;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			num_rays;
	int			win_width;
	int			win_height;
	int			need_drawing;
	t_player	*player;
	t_file		*file;
	t_texture	*frame;
	t_texture	*tex_no;
	t_texture	*tex_so;
	t_texture	*tex_we;
	t_texture	*tex_ea;
}	t_data;

/* ------------------SHARE VARIABLES ------------------ */
typedef struct s_check_map
{
	size_t	len;
	int		flag;
	int		i;
	int		j;
}	t_check_map;

typedef struct s_draw_rays
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}	t_draw_rays;

typedef struct s_draw_ray
{
	int		dx;
	int		dy;
	int		i;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
}	t_draw_ray;

typedef struct s_draw_3d
{
	int		i;
	int		x;
	float	wall_x;
}	t_draw_3d;

typedef struct s_draw_textured_line
{
	int				y;
	int				tex_x;
	int				tex_y;
	float			step;
	float			tex_pos;
	unsigned int	color;

}	t_draw_textured_line;

typedef struct s_cast_ray
{
	int		h_x;
	int		h_y;
	int		v_x;
	int		v_y;
	float	h_dist;
	float	v_dist;

}	t_cast_ray;
#endif
