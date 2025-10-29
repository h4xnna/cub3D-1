/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:24:03 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/29 16:12:55 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# define PI 3.1415926535
# define WIDTH 1280
# define HEIGHT 720
# define FAILURE 1
# define SUCCESS 0
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC_KEY 65307
# define SIZE_SQUARE 15
# define BLANC 0xFFFFFF
# define NOIR 0x000000
# define ROUGE 0xFF0000
# define TEAL 0x008080
# define ROTSPEED 0.05
# define VERT 0x006400
# define MINIMAP_RADIUS 5
# define RED "\033[1;31m"
# define RESET "\033[0m"

typedef struct s_color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
}	t_color;

typedef struct s_info_pars
{
	char		**line_split;
	char		**colors;

}				t_info_pars;

typedef struct s_map_pars
{
	char		**map;
	char		position;
	int			width;
	int			height;
	int			close;
	int			x_start;
	int			y_start;
	int			map_started;
}				t_map_pars;

typedef struct s_player // position
{
	float pa;
	double pdirx;
	double pdiry;
	double px;
	double py;
	double planex;
	double planey;
	bool	moving_right;
	bool	moving_left;
	bool	moving_up;
	bool	moving_down;
	bool	rotate_right;
	bool	rotate_left;
}				t_player;

typedef struct s_map_info
{
	char		*south;
	char		*west;
	char		*east;
	char		*north;
	int			*floor;
	int			*ceiling;
	int			count_info;
}				t_map_info;

typedef struct s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

}				t_win;

typedef struct s_raycast
{
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perpwall_dist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_raycast;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx;
}				t_img;

typedef struct s_texture
{
	t_img		skybox;
	t_img		floor;
	t_img		text_South;
	t_img		text_North;
	t_img		text_West;
	t_img		text_East;
}				t_texture;

typedef struct s_data
{
	t_map_pars	map_pars;
	t_info_pars	info_pars;
	t_map_info	map_info;
	t_player	player;
	t_win		win;
	t_raycast	raycast;
	t_texture	texture;
}				t_data;

// utils_pars1
int				get_texture_pixel(t_img *img, int x, int y);
int				len_tab(char **tab);
char			*remove_newline(char *line);
int				ft_strcmp(char *str, char *str2);
int				is_fichier(char *path);
int				is_direction(char *str);
void			drawRays2D(t_data *data);

// utils_pars2
void			print_info(t_map_info info, t_map_pars map);
void			fill_struct(t_map_info *infos, char *direction, char *path);
void			stock_colors(t_map_info *infos, t_info_pars *pars, int nb,
					int i);
int				allouer_colors(t_info_pars *pars, t_map_info *infos);
void			print_char(char **str);

// utils_pars3
void			error_message(char *error);
int				check_infos(t_map_info *info);
int				check_cub(char *str);
int				checks_args(int ac, char **av);
void			*ft_realloc(void *ptr, size_t new_size);

// pars_map
int				check_positions(t_map_pars *map, char *line);
int				add_line_to_map(t_map_pars *map, char *line);
int				check_char(char *line, t_map_pars *map);
int				is_full_of_spaces(char *line);
int				check_fd(int *fd, char **av);

// free_pars1
void			free_info(t_map_info *info);
void			free_tab(char **tab);
void			free_pars(t_info_pars *pars);

// pars_map2
void			print_char(char **str);
int				print_tab(int *tab);
int				skip_space(char *line);
long long		ft_atoll(const char *nptr);

// info_pars4
int				pars_info(t_info_pars *pars, t_map_info *infos);
int				flood_fill(t_map_pars *map);

// buttons
void			buttons_a(t_player *player, t_map_pars *map);
void			buttons_d(t_player *player, t_map_pars *map);
void			buttons_w(t_player *player, t_map_pars *map);
void			buttons_s(t_player *player, t_map_pars *map);

// draw_map2D
void			x_to_0(t_map_pars *map);
void			draw_square(t_data *data, int x, int y, int color,
					int square_size);
void			draw_map(t_data *data);
int				is_wall(t_data *data, float ray_x, float ray_y);
void			draw_line(t_data *data);

// player_position
void			set_player_direction(t_player *player, char direction);
int				rgb_to_hex_int(t_data *data, int *rgb);

// exec../texture
void			load_all_textures(t_data *data);
void			load_text(t_data *data);

// exec../ util_win
void			split_win(t_data *data);
void			my_mlx_pixel_put(t_win *win, int x, int y, int color);
void			clear_window(t_win *win);
t_win			*init_win(void);
void			free_win(t_win *win);

// utils_main
int				init_structs(t_map_pars *map, t_map_info *infos,
					t_info_pars *pars, int *fd, t_data *data);
int				parse_info_line(char *line, t_info_pars *pars,
					t_map_info *infos);
int				parse_error(t_map_pars *map, t_map_info *infos,
					t_info_pars *pars, char *msg);
int				final_checks(t_map_info *infos, t_map_pars *map);
int				parse_file(int fd, t_map_pars *map, t_map_info *infos,
					t_info_pars *pars);

// utils_main2
int				render(t_data *data);
void			clean_exit(t_data *data);
int				mouse_info(int x, int y, t_data *data);
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);

// animation
void			normalize_vector(double *x, double *y);
void			drawSkybox(t_data *data);


#endif