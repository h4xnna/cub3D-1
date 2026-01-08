/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:23:04 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/08 10:51:06 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	splice_colors(t_color *floort, t_color *wall, t_color *reflect)
{
	floort->r = (floor_color >> 16) & 0xFF;
	floort->g = (floor_color >> 8) & 0xFF;
	floort->b = floor_color & 0xFF;
	reflect->r = (reflected_color >> 16) & 0xFF;
	reflect->g = (reflected_color >> 8) & 0xFF;
	reflect->b = reflected_color & 0xFF;
	wall->r = (wall_color >> 16) & 0xFF;
	wall->g = (wall_color >> 8) & 0xFF;
	wall->b = wall_color & 0xFF;
}

static unsigned int	make_final_color(unsigned int floor_color,
		unsigned int reflected_color, unsigned int wall_color)
{
	t_color			floort;
	t_color			wall;
	t_color			reflect;
	t_color			final;
	unsigned int	final_color;

	splice_colors(&floort, &wall, &reflect);
	final.r = (uint8_t)((floort.r * FLOOR_W + reflect.r
				* REFLECT_W + wall.r * WALL_W));
	final.g = (uint8_t)((floort.g * FLOOR_W + reflect.g
				* REFLECT_W + wall.g * WALL_W));
	final.b = (uint8_t)((floort.b * FLOOR_W + reflect.b
				* REFLECT_W + wall.b * WALL_W));
	final_color = (final.r << 16) | (final.g << 8) | final.b;
	return (final_color);
}

static unsigned int	sample_floor_color(t_data *data, t_point f_coords,
		int *is_floor)
{
	t_img	*ftex;
	int		ftex_x;
	int		ftex_y;
	int		floor_color;
	t_color	exit_color;

	if ((f_coords.y > 0 && f_coords.y < data->map_pars->height)
		&& data->map_pars->map[(int)f_coords.y][(int)f_coords.x] == 'L')
	{
		ftex = data->texture->exit;
		ftex_x = (int)(f_coords.x * ftex->width) % ftex->width;
		ftex_y = (int)(f_coords.y * ftex->height) % ftex->height;
		floor_color = ((int *)ftex->addr)[ftex->width * ftex_y + ftex_x];
		exit_color.g = (floor_color >> 8) & 0xFF;
		if (exit_color.g > 0)
			ftex = data->texture->floor;
	}
	else
		ftex = data->texture->floor;
	ftex_x = (int)(f_coords.x * ftex->width) % ftex->width;
	ftex_y = (int)(f_coords.y * ftex->height) % ftex->height;
	floor_color = ((int *)ftex->addr)[ftex->width * ftex_y + ftex_x];
	*is_floor = (ftex == data->texture->floor);
	return (floor_color);
}

static void	compute_floor_coords(t_data *data, int p, t_point floor_coords,
		t_point *current_floor_coords)
{
	double	weight;

	weight = (HEIGHT / (2.0 * p - HEIGHT)) / data->raycast->perpwall_dist;
	current_floor_coords->x = weight * floor_coords.x + (1.0 - weight)
		* data->player->px;
	current_floor_coords->y = weight * floor_coords.y + (1.0 - weight)
		* data->player->py;
}

void	render_floor_pixel(t_data *data, int x, int p, t_point floor_coords)
{
	t_point			current_floor_coords;
	unsigned int	floor_color;
	int				is_floor;
	int				reflected_color;
	int				wall_color;

	is_floor = true;
	if (data->map_info->has_floor)
	{
		compute_floor_coords(data, p, floor_coords, &current_floor_coords);
		floor_color = sample_floor_color(data, current_floor_coords, &is_floor);
	}
	else
		floor_color = data->texture->floor_color;
	reflected_color = 0;
	wall_color = 0;
	if (is_floor)
	{
		reflected_color = get_window_pixel(data->win, x, HEIGHT - p);
		wall_color = get_window_pixel(data->win, x, p);
	}
	my_mlx_pixel_put(data->win, x, p, apply_shading((HEIGHT / (2.0 * p
					- HEIGHT)) / 2, make_final_color(floor_color,
				reflected_color, wall_color)));
}
