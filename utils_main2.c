/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:54:11 by hmimouni          #+#    #+#             */
/*   Updated: 2025/11/06 11:20:10 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_camera_right(t_data *data)
{
	double oldDirX = data->player->pdirx;
	data->player->pdirx = data->player->pdirx * cos(ROTSPEED) - data->player->pdiry * sin(ROTSPEED);
	data->player->pdiry = oldDirX * sin(ROTSPEED) + data->player->pdiry * cos(ROTSPEED);
	double oldPlaneX = data->player->planex;
	data->player->planex = data->player->planex * cos(ROTSPEED) - data->player->planey * sin(ROTSPEED);
	data->player->planey = oldPlaneX * sin(ROTSPEED) + data->player->planey * cos(ROTSPEED);
	normalize_vector(&data->player->pdirx, &data->player->pdiry);
	normalize_vector(&data->player->planex, &data->player->planey);
}

void move_camera_left(t_data *data)
{
	double oldDirX = data->player->pdirx;
	data->player->pdirx = data->player->pdirx * cos(-ROTSPEED) - data->player->pdiry * sin(-ROTSPEED);
	data->player->pdiry = oldDirX * sin(-ROTSPEED) + data->player->pdiry * cos(-ROTSPEED);
	double oldPlaneX = data->player->planex;
	data->player->planex = data->player->planex * cos(-ROTSPEED) - data->player->planey * sin(-ROTSPEED);
	data->player->planey = oldPlaneX * sin(-ROTSPEED) + data->player->planey * cos(-ROTSPEED);
	normalize_vector(&data->player->pdirx, &data->player->pdiry);
	normalize_vector(&data->player->planex, &data->player->planey);
}

int render(t_data *data)
{
	clear_window(data->win);
	drawRays2D(data);
	return (0);
}

void free_textures(t_data *data)
{
	if (data->texture->text_East->img)
		mlx_destroy_image(data->win->mlx, data->texture->text_East->img);
	if (data->texture->text_North->img)
		mlx_destroy_image(data->win->mlx, data->texture->text_North->img);
	if (data->texture->text_South->img)
		mlx_destroy_image(data->win->mlx,data->texture->text_South->img);
	if (data->texture->text_West->img)
		mlx_destroy_image(data->win->mlx, data->texture->text_West->img);
}

void	clean_exit(t_data *data)
{
	free_textures(data);
	free_win(data->win);
	free_info(data->map_info);
	free_tab(data->map_pars->map);
	exit(0);
}