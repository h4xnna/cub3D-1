/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:13:48 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/29 18:14:13 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_camera_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player->pdirx;
	data->player->pdirx = data->player->pdirx * cos(ROTSPEED)
		- data->player->pdiry * sin(ROTSPEED);
	data->player->pdiry = old_dir_x * sin(ROTSPEED) + data->player->pdiry
		* cos(ROTSPEED);
	old_plane_x = data->player->planex;
	data->player->planex = data->player->planex * cos(ROTSPEED)
		- data->player->planey * sin(ROTSPEED);
	data->player->planey = old_plane_x * sin(ROTSPEED) + data->player->planey
		* cos(ROTSPEED);
	normalize_vector(&data->player->pdirx, &data->player->pdiry);
	normalize_vector(&data->player->planex, &data->player->planey);
}

void	move_camera_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player->pdirx;
	data->player->pdirx = data->player->pdirx * cos(-ROTSPEED)
		- data->player->pdiry * sin(-ROTSPEED);
	data->player->pdiry = old_dir_x * sin(-ROTSPEED) + data->player->pdiry
		* cos(-ROTSPEED);
	old_plane_x = data->player->planex;
	data->player->planex = data->player->planex * cos(-ROTSPEED)
		- data->player->planey * sin(-ROTSPEED);
	data->player->planey = old_plane_x * sin(-ROTSPEED) + data->player->planey
		* cos(-ROTSPEED);
	normalize_vector(&data->player->pdirx, &data->player->pdiry);
	normalize_vector(&data->player->planex, &data->player->planey);
}

void	normalize_vector(double *x, double *y)
{
	double	length;

	length = sqrt((*x) * (*x) + (*y) * (*y));
	if (length != 0)
	{
		*x /= length;
		*y /= length;
	}
}