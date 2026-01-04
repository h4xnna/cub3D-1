/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:26:28 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/04 13:57:43 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

void	init_raycasting(t_data *data, int x)
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
