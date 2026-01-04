/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:11:42 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/04 13:57:24 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	compute_floor_wall_coords(t_data *data, double wall_x,
		t_point *floor_coords)
{
	if (data->raycast->side == 0 && data->raycast->raydirx > 0)
	{
		floor_coords->x = data->raycast->mapx;
		floor_coords->y = data->raycast->mapy + wall_x;
	}
	else if (data->raycast->side == 0 && data->raycast->raydirx < 0)
	{
		floor_coords->x = data->raycast->mapx + 1.0;
		floor_coords->y = data->raycast->mapy + wall_x;
	}
	else if (data->raycast->side == 1 && data->raycast->raydiry > 0)
	{
		floor_coords->x = data->raycast->mapx + wall_x;
		floor_coords->y = data->raycast->mapy;
	}
	else
	{
		floor_coords->x = data->raycast->mapx + wall_x;
		floor_coords->y = data->raycast->mapy + 1.0;
	}
}

static void	render_wall_pixels(t_data *data, int x, int y, unsigned int color)
{
	my_mlx_pixel_put(data->win, x, y, color);
	if ((y + (data->raycast->draw_end - y) * 2) < HEIGHT)
	{
		my_mlx_pixel_put(data->win, x, y + (data->raycast->draw_end - y)
			* 2, color);
	}
}

static void	draw_wall(t_data *data, int x, double wall_x)
{
	int				tex_x;
	int				tex_y;
	int				y;
	int				d;
	unsigned int	color;

	tex_x = (int)(wall_x * (double)data->raycast->tex->width);
	if ((data->raycast->side == 0 && data->raycast->raydirx > 0)
		|| (data->raycast->side == 1 && data->raycast->raydiry < 0))
		tex_x = data->raycast->tex->width - tex_x - 1;
	y = data->raycast->draw_start;
	while (y <= data->raycast->draw_end)
	{
		d = y * 256 - HEIGHT * 128 + data->raycast->line_height * 128;
		tex_y = ((d * data->raycast->tex->height) / data->raycast->line_height)
			/ 256;
		if (tex_y < 0)
			tex_y = 0;
		color = ((int *)data->raycast->tex->addr)[data->raycast->tex->height
			* tex_y + tex_x];
		color = apply_shading(data->raycast->perpwall_dist / 2, color);
		render_wall_pixels(data, x, y, color);
		y++;
	}
}

void	raycasting(t_data *data)
{
	int		x;
	int		p;
	double	wall_x;
	t_point	floor_coords;

	x = 0;
	wall_x = 0.0;
	while (x < WIDTH)
	{
		init_raycasting(data, x);
		perform_dda(data, &wall_x);
		draw_wall(data, x, wall_x);
		compute_floor_wall_coords(data, wall_x, &floor_coords);
		p = data->raycast->draw_end;
		while (p < HEIGHT)
		{
			render_floor_pixel(data, x, p, floor_coords);
			p++;
		}
		x++;
	}
}
