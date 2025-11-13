/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:51:35 by hmimouni          #+#    #+#             */
/*   Updated: 2025/11/13 08:00:15 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->pdirx = 0;
		player->pdiry = -1;
		player->planex = 0.66;
		player->planey = 0;
	}
	else if (direction == 'S')
	{
		player->pdirx = 0;
		player->pdiry = 1;
		player->planex = -0.66;
		player->planey = 0;
	}
	else if (direction == 'E')
	{
		player->pdirx = 1;
		player->pdiry = 0;
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

void rotate_player(t_data *data, int mouse_x)
{
	static double current_speed = 0.0;
 
	double max_speed = 0.15;

	if (data->player->rotate_right)
		mouse_x = WIDTH / 2 + ROTSPEED;
	else if (data->player->rotate_left)
		mouse_x = WIDTH / 2 - ROTSPEED;
	double target_speed = data->player->sensitivity * (mouse_x - WIDTH/2);

    if (target_speed > max_speed)
		target_speed = max_speed;
	if (target_speed < -max_speed)
		target_speed = -max_speed;

    double accel = 15.0;
    current_speed += (target_speed - current_speed) * accel * data->player->delta_time;

	double oldDirX = data->player->pdirx;
	data->player->pdirx = data->player->pdirx * cos(current_speed) - data->player->pdiry * sin(current_speed);
	data->player->pdiry = oldDirX * sin(current_speed) + data->player->pdiry * cos(current_speed);
	double oldPlaneX = data->player->planex;
	data->player->planex = data->player->planex * cos(current_speed) - data->player->planey * sin(current_speed);
	data->player->planey = oldPlaneX * sin(current_speed) + data->player->planey * cos(current_speed);
	normalize_vector(&data->player->pdirx, &data->player->pdiry);
	normalize_vector(&data->player->planex, &data->player->planey);

	mlx_mouse_move(data->win->mlx, data->win->win, WIDTH / 2, HEIGHT / 2);
}

void player_position(t_data *data)
{
	static bool	exited = 0;
	if (!exited)
	{
		if (data->player->moving_left)
			buttons_a(data->player, data->map_pars);
		if (data->player->moving_right)
			buttons_d(data->player, data->map_pars);
		if(data->player->moving_down)
			buttons_s(data->player, data->map_pars);
		if(data->player->moving_up)
			buttons_w(data->player, data->map_pars);
		if(data->map_pars->map[(int)data->player->py][(int)(data->player->px)] == 'L')
			exited = 1;
	}
	else
	{
		data->player->pitch -= 50;
		if (data->player->pitch < -5000)
			clean_exit(data);
	}
		
}

int	rgb_to_hex_int(t_data *data, int *rgb)
{
	int	r;
	int	g;
	int	b;

	if (!rgb)
	{
		error_message(" RGB pointer is NULL.");
		clean_exit(data);
	}
	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		error_message("Valeur RGB invalide.");
		clean_exit(data);
	}
	return ((r << 16) | (g << 8) | b);
}


