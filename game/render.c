/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 07:53:02 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/07 15:56:26 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_delta_time(t_data *data)
{
	static double	last_time = 0;
	double			current_time;

	current_time = get_time_seconds();
	data->player->delta_time = current_time - last_time;
	if (data->player->delta_time >= 1)
		data->player->delta_time = 0.016;
	last_time = current_time;
}

void	draw_skycolor(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y <= HEIGHT / 2)
		{
			my_mlx_pixel_put(data->win, x, y, data->texture->skycolor);
			y++;
		}
		x++;
	}
}

static void	draw_sky(t_data *data)
{
	if (data->map_info->has_skybox)
		draw_skybox(data);
	else
		draw_skycolor(data);
}

int	render(t_data *data)
{
	get_delta_time(data);
	data->fps = ft_itoa(1.0 / data->player->delta_time);
	if (!data->fps)
		clean_exit(data);
	clear_window(data->win);
	draw_sky(data);
	raycasting(data);
	draw_minimap(data);
	player_position(data);
	rotate_player(data, data->player->mouse_x);
	update_doors(data);
	update_animations(data);
	display_overlay(data);
	mlx_put_image_to_window(data->win->mlx, data->win->win, data->win->img, 0,
		0);
	mlx_string_put(data->win->mlx, data->win->win, WIDTH - 20, 20, 0xFFFFFF,
		data->fps);
	free(data->fps);
	data->fps = NULL;
	return (0);
}
