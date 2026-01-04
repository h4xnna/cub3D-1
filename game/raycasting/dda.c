/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:13:29 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/04 13:57:12 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	get_wall_x(t_data *data, double *wall_x)
{
	t_door	*door;

	if (data->raycast->side == 0)
		*wall_x = data->player->py + data->raycast->perpwall_dist
			* data->raycast->raydiry;
	else
		*wall_x = data->player->px + data->raycast->perpwall_dist
			* data->raycast->raydirx;
	*wall_x -= floor(*wall_x);
	if (data->map_pars->map[data->raycast->mapy][data->raycast->mapx] == 'D'
		&& data->raycast->skip == false)
	{
		door = find_door(data->doors, data->raycast->mapy, data->raycast->mapx);
		*wall_x -= door->opening;
		if (*wall_x <= 0.0)
		{
			data->raycast->skip = true;
			data->raycast->hit = 0;
		}
	}
}

static void	choose_texture(t_data *data)
{
	if (data->raycast->side == 0)
	{
		if (data->raycast->raydirx > 0)
			data->raycast->tex = data->texture->text_west;
		else
			data->raycast->tex = data->texture->text_east;
	}
	else
	{
		if (data->raycast->raydiry > 0)
			data->raycast->tex = data->texture->text_north;
		else
			data->raycast->tex = data->texture->text_south;
	}
}

static void	init_drawing(t_data *data)
{
	if (data->raycast->side == 0)
		data->raycast->perpwall_dist = data->raycast->sidedistx
			- data->raycast->delta_dist_x;
	else
		data->raycast->perpwall_dist = data->raycast->side_dist_y
			- data->raycast->delta_dist_y;
	data->raycast->line_height = (int)(HEIGHT / data->raycast->perpwall_dist);
	data->raycast->draw_start = -data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_start < 0)
		data->raycast->draw_start = 0;
	data->raycast->draw_end = data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_end >= HEIGHT)
		data->raycast->draw_end = HEIGHT - 1;
}

static void	step_through(t_data *data)
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
}

void	perform_dda(t_data *data, double *wall_x)
{
	int	mapx;
	int	mapy;

	data->raycast->skip = false;
	data->raycast->hit = 0;
	while (data->raycast->hit == 0)
	{
		step_through(data);
		mapx = data->raycast->mapx;
		mapy = data->raycast->mapy;
		if (data->map_pars->map[mapy] && (data->map_pars->map[mapy][mapx] == '1'
			|| (data->map_pars->map[mapy][mapx] == 'D'
			&& data->raycast->skip == false)))
			data->raycast->hit = 1;
		else
			continue ;
		init_drawing(data);
		choose_texture(data);
		get_wall_x(data, wall_x);
		data->raycast->skip = false;
	}
}
