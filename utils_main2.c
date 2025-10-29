/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:54:11 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/29 16:53:51 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void player_position(t_data *data)
{
	if (data->player->rotate_left)
		move_camera_left(data);
	else if (data->player->rotate_right)
		move_camera_right(data);
	if (data->player->moving_left)
		buttons_a(data->player, data->map_pars);
	if (data->player->moving_right)
		buttons_d(data->player, data->map_pars);
	if(data->player->moving_down)
		buttons_s(data->player, data->map_pars);
	if(data->player->moving_up)
		buttons_w(data->player, data->map_pars);
}

int render(t_data *data)
{
	clear_window(data->win);
	drawSkybox(data);
	drawRays2D(data);
	player_position(data);
	mlx_mouse_move(data->win->mlx, data->win->win, WIDTH / 2, HEIGHT / 2);
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