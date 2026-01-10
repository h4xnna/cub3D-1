/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:51:22 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/10 17:25:43 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_step_side_dist(t_data *data)
{
	if (data->raycast->raydirx < 0)
	{
		data->raycast->stepx = -1;
		data->raycast->sidedistx = (data->player->px - data->raycast->mapx)
			* data->raycast->delta_dist_x;
	}
	else
	{
		data->raycast->stepx = 1;
		data->raycast->sidedistx = (data->raycast->mapx + 1.0
				- data->player->px) * data->raycast->delta_dist_x;
	}
	if (data->raycast->raydiry < 0)
	{
		data->raycast->stepy = -1;
		data->raycast->side_dist_y = (data->player->py - data->raycast->mapy)
			* data->raycast->delta_dist_y;
	}
	else
	{
		data->raycast->stepy = 1;
		data->raycast->side_dist_y = (data->raycast->mapy + 1.0
				- data->player->py) * data->raycast->delta_dist_y;
	}
}

static void	init_raycasting(t_data *data, int x)
{
	data->raycast->camerax = 2 * x / (double)WIDTH - 1;
	data->raycast->raydirx = data->player->pdirx + data->player->planex
		* data->raycast->camerax;
	data->raycast->raydiry = data->player->pdiry + data->player->planey
		* data->raycast->camerax;
	if (data->raycast->raydirx == 0)
		data->raycast->raydirx = 0.001;
	if (data->raycast->raydiry == 0)
		data->raycast->raydiry = 0.001;
	data->raycast->mapx = (int)data->player->px;
	data->raycast->mapy = (int)data->player->py;
	data->raycast->delta_dist_x = fabs(1 / data->raycast->raydirx);
	data->raycast->delta_dist_y = fabs(1 / data->raycast->raydiry);
	init_step_side_dist(data);
}

static void	perform_dda(t_data *data)
{
	data->raycast->hit = 0;
	while (data->raycast->hit == 0)
	{
		if (data->raycast->sidedistx < data->raycast->side_dist_y)
		{
			data->raycast->sidedistx += data->raycast->delta_dist_x;
			data->raycast->mapx += data->raycast->stepx;
			data->raycast->side = 0;
		}
		else
		{
			data->raycast->side_dist_y += data->raycast->delta_dist_y;
			data->raycast->mapy += data->raycast->stepy;
			data->raycast->side = 1;
		}
		if (data->map_pars->map[data->raycast->mapy]
			&& (data->map_pars->map[data->raycast->mapy][data->raycast->mapx]
			== '1'))
			data->raycast->hit = 1;
	}
}

void	raycasting(t_data *data)
{
	int		x;
	int		tex_x;
	t_img	*texture;

	x = 0;
	while (x < WIDTH)
	{
		init_raycasting(data, x);
		perform_dda(data);
		get_perp_wall_dist(data);
		calculate_line(data);
		get_wall_texture(data, &texture);
		get_texture_x(data, texture, &tex_x);
		draw_line(data, texture, tex_x, x);
		x++;
	}
	mlx_put_image_to_window(data->win->mlx, data->win->win, data->win->img, 0,
		0);
}
