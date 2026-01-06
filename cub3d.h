/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:24:03 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/06 11:21:41 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "assets/libs/gnl/get_next_line.h"
# include "assets/libs/libft/libft.h"
# include "assets/libs/minilibx-linux/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>

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
# define SQUARE_SIZE 15
# define BLANC 0xFFFFFF
# define NOIR 0x000000
# define ROUGE 0xFF0000
# define TEAL 0x008080
# define ROTSPEED 25
# define VERT 0x006400
# define MINIMAP_RADIUS 5
# define REFLECTIONSTRENGTH 0.1
# define RED "\033[1;31m"
# define RESET "\033[0m"
# define MOVE_SPEED 3

typedef struct s_color
{
	uint8_t				r;
	uint8_t				g;
	uint8_t				b;
}						t_color;

typedef struct s_point
{
	double				x;
	double				y;
}						t_point;

typedef struct s_info_pars
{
	char				**line_split;
	char				**colors;

}						t_info_pars;

typedef struct s_map_pars
{
	char				**map;
	char				position;
	int					width;
	int					height;
	int					close;
	int					x_start;
	int					y_start;
	int					map_started;
}						t_map_pars;

// typedef struct s_init
// {
// 	t_map_pars			**map;
// 	t_map_info			**infos;
// 	t_info_pars			**pars;
// 	t_data				**data;
// 	int					*fd;
// }	t_init;

typedef struct s_player
{
	float				pa;
	double				pdirx;
	double				pdiry;
	double				px;
	double				py;
	double				planex;
	double				planey;
	bool				moving_right;
	bool				moving_left;
	bool				moving_up;
	bool				moving_down;
	bool				rotate_right;
	bool				rotate_left;
	double				rotate_speed;
	double				sensitivity;
	double				pitch;
	double				delta_time;
	int					mouse_x;
	int					mouse_y;
	bool				show_knife;

}						t_player;

typedef struct s_map_info
{
	char				*south;
	char				*west;
	char				*east;
	char				*north;
	int					*floor;
	int					*ceiling;
	int					count_info;
}						t_map_info;

typedef struct s_win
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;

}						t_win;

typedef struct s_img
{
	void				*img;
	char				*addr;
	int					width;
	int					height;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	void				*mlx;
}						t_img;

typedef struct s_animation
{
	t_img				**frames;
	int					frame_count;
	int					current_frame;
	double				frame_time;
	double				timer;
	double				duration;
	int					playing;
}						t_animation;

typedef struct s_door
{
	int					x;
	int					y;
	double				opening;
	int					opened;
	struct s_door		*next;
}						t_door;

typedef struct s_raycast
{
	double				camerax;
	double				raydirx;
	double				raydiry;
	int					mapx;
	int					mapy;
	double				sidedistx;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perpwall_dist;
	int					stepx;
	int					stepy;
	int					hit;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
	t_img				*tex;
	bool				skip;
}						t_raycast;

typedef struct s_texture
{
	t_img				*skybox;
	t_img				*floor;
	t_img				*door;
	t_img				*exit;
	t_img				*text_south;
	t_img				*text_north;
	t_img				*text_west;
	t_img				*text_east;
}						t_texture;

typedef struct s_data
{
	t_map_pars			*map_pars;
	t_info_pars			*info_pars;
	t_map_info			*map_info;
	t_player			*player;
	t_win				*win;
	t_raycast			*raycast;
	t_texture			*texture;
	t_door				*doors;
	t_animation			*knife_anim;
	t_animation			*deploy_anim;
	t_animation			*lmb_anim;
	t_animation			*rmb_anim;
	int					fd;
	char				*fps;
}						t_data;

static inline int	get_window_pixel(t_win *win, int x, int y)
{
	char	*dst;

	if (!win->addr)
		return (0);
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return (0);
	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static inline void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	if (!win || !win->addr)
		return ;
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static inline uint32_t	apply_shading(double distance, uint32_t color)
{
	t_color		rgb;
	t_color		new_rgb;
	double		factor;
	uint32_t	new_color;

	if (distance < 1.0)
		distance = 1.0;
	factor = 1.0 / distance;
	if (factor < 0.1)
		factor = 0.1;
	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	new_rgb.r = (uint8_t)(rgb.r * factor);
	new_rgb.g = (uint8_t)(rgb.g * factor);
	new_rgb.b = (uint8_t)(rgb.b * factor);
	new_color = (new_rgb.r << 16) | (new_rgb.g << 8) | new_rgb.b;
	return (new_color);
}

static inline int	get_texture_pixel(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

// utils_pars1
void					update_doors(t_data *data);
t_door					*find_door(t_door *doors, int y, int x);
void					update_animations(t_data *data);
void					display_overlay(t_data *data);
void					free_textures(t_data *data);
void					free_data(t_data *data);
void					clean_exit(t_data *data);
void					free_texture(t_img *texture, void *mlx);

int						init_data(t_data **data, int fd);
void					draw_skybox(t_data *data);
void					draw_image_to_buffer(t_win *win, t_img *src, int x_off,
						int y_off);
void					rotate_player(t_data *data, int mouse_x);
void					print_doors(t_door *doors);
void					make_doors(t_data *data);
t_door					*find_door(t_door *doors, int y, int x);
int						mouse_hook(int keycode, int x, int y, t_data *data);
int						len_tab(char **tab);
char					*remove_newline(char *line);
int						ft_strcmp(char *str, char *str2);
int						is_fichier(char *path);
int						is_direction(char *str);
void					free_splif(char **out, int i);

// utils_pars2
void					print_info(t_map_info info, t_map_pars map);
void					fill_struct(t_map_info *infos, char *direction,
						char *path);
void					stock_colors(t_map_info *infos, t_info_pars *pars,
						int nb, int i);
int						allouer_colors(t_info_pars *pars, t_map_info *infos);
void					print_char(char **str);

// utils_pars3
void					error_message(char *error);
int						check_infos(t_map_info *info);
int						check_cub(char *str);
int						checks_args(int ac, char **av);
void					*ft_realloc(void *ptr, size_t new_size);

// pars_map
int						check_positions(t_map_pars *map, char *line);
int						add_line_to_map(t_map_pars *map, char *line);
int						check_char(char *line, t_map_pars *map);
int						is_full_of_spaces(char *line);
int						check_fd(int *fd, char **av);
void					player_position(t_data *data);

// free_pars1
void					free_info(t_map_info *info);
void					free_tab(char **tab);
void					free_pars(t_info_pars *pars);

// pars_map2
void					print_char(char **str);
int						print_tab(int *tab);
int						skip_space(char *line);
long long				ft_atoll(const char *nptr);

// info_pars4
int						pars_info(t_info_pars *pars, t_map_info *infos);
int						flood_fill(t_map_pars *map);
int						count_coma(char *line);
int						remplir_colors(t_info_pars *pars, t_map_info *infos);

// info_pars6
int						pars_info_else(t_info_pars *pars, t_map_info *infos);
int						pars_info(t_info_pars *pars, t_map_info *infos);

// buttons
void					buttons_a(t_player *player, t_map_pars *map);
void					buttons_d(t_player *player, t_map_pars *map);
void					buttons_w(t_player *player, t_map_pars *map);
void					buttons_s(t_player *player, t_map_pars *map);

// draw_map2D
void					draw_minimap(t_data *data);
bool					is_walkable(char c);
double					get_time_seconds(void);
void					make_color_from_int(unsigned int color, t_color *rgb);
void					reset_all_animations(t_data *data);

// player_position
void					set_player_direction(t_player *player, char direction);
int						rgb_to_hex_int(t_data *data, int *rgb);

// exec../texture
void					load_animations(t_data *data);
void					load_textures(t_data *data);

// exec../ util_win
void					clear_window(t_win *win);
t_win					*init_win(void);
void					free_win(t_win *win);
void					raycasting(t_data *data);

// utils_main
void					perform_dda(t_data *data, double *wall_x);
void					init_raycasting(t_data *data, int x);
void					render_floor_pixel(t_data *data, int x, int p,
						t_point floor_coords);
int						parse_info_line(char *line, t_info_pars *pars,
						t_map_info *infos);
int						parse_error(char *msg);
int						final_checks(t_map_info *infos, t_map_pars *map);
int						parse_file(int fd, t_map_pars *map, t_map_info *infos,
						t_info_pars *pars);

// utils_main2
int						render(t_data *data);
void					clean_exit(t_data *data);
int						mouse_info(int x, int y, t_data *data);
int						key_press(int keycode, t_data *data);
int						key_release(int keycode, t_data *data);

// animation
void					normalize_vector(double *x, double *y);

#endif