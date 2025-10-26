/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbounoui <mbounoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:43:11 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/17 10:31:03 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "/home/kbouarfa/minilibx-linux/mlx.h"
# include "/home/kbouarfa/minilibx-linux/mlx_int.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 50

# define RED "\e[1;31m"
# define BLUE "\e[1;34m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[1;93m"
# define PINK "\e[1;4;38;5;198m" 

# define INVALID_CHAR "INVALID CHARACTER"
# define INVALID_ARGS "INVALID PROGRAM INPUT"
# define MALLOC_FAILED "MALLOC FAILED"
# define HOLE_IN_MAP "MAP HAS A HOLE"
# define MISSING_DIR_CHAR "MISSING DIRECTION CHARACTER"
# define MISSING_COLOR "MISSING FLOOR OR CIEL COLOR"
# define MISSING_TEXTURE "MISSING TEXTURE"
# define INVALID_TEXTURE "INVALID TEXTURE"
# define DOUBLE_DIR_CHAR "DOUBLE DIRECTION CHARACTER"
# define INVALID_EXT "INVALID FILE EXTENSION"
# define INVALID_LINE "INVALID LINE IN MAP"
# define COLOR_RANGE_OUT "COLOR RANGE OUT <0 - 255>"
# define MORE_THAN_FOUR "COLORS ARE MORE THAN THREE"
# define SOMETHING_AFTER_MAP "THERE IS SOMETHING AFTER MAP"
# define HAS_CHAR "COLORS MUST BE ONLY DIGITS"
# define INVALID_MAP "NO MAP"

# define NO 1
# define EA 2
# define SO 3
# define WE 4

# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define THREE_D 1
# define CUB 1
# define SQUERE 60
# define RES 1

// PARSSING
int				check_extension(char *path, int flag);
int				check_path(char *path);
int				array_len(char **arr);
int				len_to_new_line(char *str);
void			skip_white_space(char *str, int *i);
int				store_textures(t_data *map, char *line);
int				store_colors(t_data *map, char *line);
int				parssing(t_data *map, char *path);
int				check_top_bottom(char *row);
int				store_map(t_data *map, char **content, int i);
int				check_map(char **map, t_data *data);
int				store_content(t_data *map);
int				check_wall(int x, int y, t_data *data);

int				allocat_data_members(t_data *map, char *path);
void			free_array(void *array, int type);
void			print_array(void *tab, int type);

// DRAWING
void			draw_rectangle(int x, int y, int h, t_data *data);
void			draw_ray(t_draw_rays *points, t_data *data);
void			draw_square(int x, int y, t_data *game, int flag);
void			draw_map(t_data *data);
void			put_pixel(int x, int y, unsigned int color, t_data *data);
void			draw_rays(t_data *data);
void			draw_3d(t_data *data);
void			draw_textured_line(t_projection proj,
					t_texture *tex, t_draw_3d *share3d, t_data *data);
// CLEAN
void			clear_image(t_data *data);
int				clean_exit(t_data *data);
void			free_images(t_data *data);
void			free_data(t_data *data);
void			free_file(t_file *file);
void			free_tab(char **tab);
void			print_exit(char *msg);
void			free_parssing(t_data *data);

// MINILIBX
int				minilibx(t_data *data);
int				draw_loop(t_data *data);
int				init_data(t_data *data);

// MOVE PLAYER
void			init_player(t_player *player);
void			move_player(t_player *player, t_data *data);
int				key_press(int key, t_data *data);
int				key_release(int key, t_player *player);

// RAY TOOLS
float			normalize_angle(float angle);
void			get_horizontal_intersection(t_data *data, float ray_angle,
					float *x, float *y);
void			get_vertical_intersection(t_data *data, float ray_angle,
					float *x, float *y);
float			calculate_distance(int x1, int y1, int x2, int y2);
int				check_facing_up(float angle);
int				check_facing_right(float angle);
void			get_horizontal_wall(t_data *data, int *x, int *y,
					float ray_angle);
void			get_vertical_wall(t_data *data, int *x, int *y,
					float ray_angle);
void			next_point(float angle, float len, t_draw_rays *ray);
void			cast_ray(t_data *data, float ray_angle, t_ray_hit *ray);

// TEXTURES
int				load_textures(t_data *data);
float			get_wall_x(t_ray_hit hit);
unsigned int	get_texture_pixel(t_texture *tex, int x, int y);
t_texture		*get_wall_texture(t_data *data, int type_of_inter);
t_texture		*load_texture(t_data *data, char *path);

// PROJECTION PLANE
void			draw_one_projection(t_draw_3d *share, t_projection proj,
					t_data *data, t_texture *tex);
void			calc_projection_height(t_projection *proj, float len,
					float ray_angle, t_data *data);
#endif
