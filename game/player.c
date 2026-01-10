/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:51:35 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/10 19:50:14 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->pdiry = -1;
		player->planex = 0.66;
		player->planey = 0;
	}
	else if (direction == 'S')
	{
		player->pdiry = 1;
		player->planex = -0.66;
		player->planey = 0;
	}
	else if (direction == 'E')
	{
		player->pdirx = 1;
		player->planex = 0;
		player->planey = 0.66;
	}
	else if (direction == 'W')
	{
		player->pdirx = -1;
		player->pdiry = 0;
		player->planex = 0;
		player->planey = -0.66;
	}
}

static void	rotate_matrix(t_data *data, double current_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player->pdirx;
	data->player->pdirx = data->player->pdirx * cos(current_speed)
		- data->player->pdiry * sin(current_speed);
	data->player->pdiry = old_dir_x * sin(current_speed) + data->player->pdiry
		* cos(current_speed);
	old_plane_x = data->player->planex;
	data->player->planex = data->player->planex * cos(current_speed)
		- data->player->planey * sin(current_speed);
	data->player->planey = old_plane_x * sin(current_speed)
		+ data->player->planey * cos(current_speed);
}

void	rotate_player(t_data *data, int mouse_x)
{
	double	max_speed;
	double	target_speed;
	double	accel;

	max_speed = 0.15;
	if (data->player->rotate_right)
		mouse_x = WIDTH / 2 + ROTSPEED;
	else if (data->player->rotate_left)
		mouse_x = WIDTH / 2 - ROTSPEED;
	target_speed = data->player->sensitivity * (mouse_x - WIDTH / 2);
	if (target_speed > max_speed)
		target_speed = max_speed;
	if (target_speed < -max_speed)
		target_speed = -max_speed;
	accel = 15.0;
	data->player->current_speed += (target_speed - data->player->current_speed)
		* accel * data->player->delta_time;
	rotate_matrix(data, data->player->current_speed);
	normalize_vector(&data->player->pdirx, &data->player->pdiry);
	normalize_vector(&data->player->planex, &data->player->planey);
	mlx_mouse_move(data->win->mlx, data->win->win, WIDTH / 2, HEIGHT / 2);
}

void	player_position(t_data *data)
{
	if (!data->player->exited)
	{
		if (data->player->moving_left)
			buttons_a(data->player, data->map_pars);
		if (data->player->moving_right)
			buttons_d(data->player, data->map_pars);
		if (data->player->moving_down)
			buttons_s(data->player, data->map_pars);
		if (data->player->moving_up)
			buttons_w(data->player, data->map_pars);
		if (data->map_pars->map[(int)data->player->py][(int)(data->player->px)]
			== 'L')
			data->player->exited = 1;
	}
}
