/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:54:11 by hmimouni          #+#    #+#             */
/*   Updated: 2025/12/16 17:21:33 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_camera_right(t_data *data)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = data->player->pdirx;
	data->player->pdirx = data->player->pdirx * cos(ROTSPEED)
		- data->player->pdiry * sin(ROTSPEED);
	data->player->pdiry = oldDirX * sin(ROTSPEED) + data->player->pdiry
		* cos(ROTSPEED);
	oldPlaneX = data->player->planex;
	data->player->planex = data->player->planex * cos(ROTSPEED)
		- data->player->planey * sin(ROTSPEED);
	data->player->planey = oldPlaneX * sin(ROTSPEED) + data->player->planey
		* cos(ROTSPEED);
	normalize_vector(&data->player->pdirx, &data->player->pdiry);
	normalize_vector(&data->player->planex, &data->player->planey);
}

void	move_camera_left(t_data *data)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = data->player->pdirx;
	data->player->pdirx = data->player->pdirx * cos(-ROTSPEED)
		- data->player->pdiry * sin(-ROTSPEED);
	data->player->pdiry = oldDirX * sin(-ROTSPEED) + data->player->pdiry
		* cos(-ROTSPEED);
	oldPlaneX = data->player->planex;
	data->player->planex = data->player->planex * cos(-ROTSPEED)
		- data->player->planey * sin(-ROTSPEED);
	data->player->planey = oldPlaneX * sin(-ROTSPEED) + data->player->planey
		* cos(-ROTSPEED);
	normalize_vector(&data->player->pdirx, &data->player->pdiry);
	normalize_vector(&data->player->planex, &data->player->planey);
}

int	render(t_data *data)
{
	clear_window(data->win);
	drawRays2D(data);
	return (0);
}

void	free_textures(t_data *data)
{
	if (data->texture)
	{
		if (data->texture->text_east->img)
			mlx_destroy_image(data->win->mlx, data->texture->text_east->img);
		if (data->texture->text_north->img)
			mlx_destroy_image(data->win->mlx, data->texture->text_north->img);
		if (data->texture->text_south->img)
			mlx_destroy_image(data->win->mlx, data->texture->text_south->img);
		if (data->texture->text_west->img)
			mlx_destroy_image(data->win->mlx, data->texture->text_west->img);
	}
}

void	clean_exit(t_data *data)
{
	if (data)
	{
		if (data->map_info)
			free_info(data->map_info);
		if (data->map_pars)
			free_tab(data->map_pars->map);
		free_textures(data);
		free_win(data->win);
	}
	exit(0);
}