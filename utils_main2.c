/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:54:11 by hmimouni          #+#    #+#             */
/*   Updated: 2025/11/04 18:39:38 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void rotate_player(t_data *data)
{
	double oldDirX = data->player->pdirx;
	data->player->pdirx = data->player->pdirx * cos(data->player->rotate_speed) - data->player->pdiry * sin(data->player->rotate_speed);
	data->player->pdiry = oldDirX * sin(data->player->rotate_speed) + data->player->pdiry * cos(data->player->rotate_speed);
	double oldPlaneX = data->player->planex;
	data->player->planex = data->player->planex * cos(data->player->rotate_speed) - data->player->planey * sin(data->player->rotate_speed);
	data->player->planey = oldPlaneX * sin(data->player->rotate_speed) + data->player->planey * cos(data->player->rotate_speed);
	normalize_vector(&data->player->pdirx, &data->player->pdiry);
	normalize_vector(&data->player->planex, &data->player->planey);
}

// void move_camera_right(t_data *data)
// {
// 	double oldDirX = data->player->pdirx;
// 	data->player->pdirx = data->player->pdirx * cos(ROTSPEED) - data->player->pdiry * sin(ROTSPEED);
// 	data->player->pdiry = oldDirX * sin(ROTSPEED) + data->player->pdiry * cos(ROTSPEED);
// 	double oldPlaneX = data->player->planex;
// 	data->player->planex = data->player->planex * cos(ROTSPEED) - data->player->planey * sin(ROTSPEED);
// 	data->player->planey = oldPlaneX * sin(ROTSPEED) + data->player->planey * cos(ROTSPEED);
// 	normalize_vector(&data->player->pdirx, &data->player->pdiry);
// 	normalize_vector(&data->player->planex, &data->player->planey);
// }

t_door	*find_door(t_door *doors, int y, int x)
{
	while (doors)
	{
		if (doors->y == y && doors->x == x)
			return (doors);
		doors = doors->next;
	}
	return (NULL);
}

void	update_doors(t_data	*data, double delta_time)
{
	t_door	*door;

	door = data->doors;
	while (door)
	{
		if (door->opened == 1 && door->opening < 1.0)
		{
			door->opening += delta_time * 0.8;
		}
		if (door->opening >= 1.0)
		{
			door->opening = 1.0;
			data->map_pars->map[door->y][door->x] = '0';
		}
		door = door->next;
	}
}

void	check_doors(t_data *data)
{
	t_player	*player = data->player;
	t_door		*door = NULL;

	if ((data->map_pars->map[(int)player->py][(int)(player->px + player->pdirx
				* 1.1)]) == 'D')
			door = find_door(data->doors, (int)player->py, (int)(player->px + player->pdirx * 1.1));
	if (data->map_pars->map[(int)(player->py + player->pdiry
			* 1.1)][(int)(player->px)] == 'D')
			door = find_door(data->doors, (int)(player->py + player->pdiry * 1.1), (int)player->px);
	if (door)
	{
		if(!door->opened)
			door->opened = 1;
	}
}

void player_position(t_data *data)
{
	if (data->player->rotate_left || data->player->rotate_right)
	{
		rotate_player(data);
		mlx_mouse_move(data->win->mlx, data->win->win, WIDTH / 2, HEIGHT / 2);
	}
	if (data->player->moving_left)
		buttons_a(data->player, data->map_pars);
	if (data->player->moving_right)
		buttons_d(data->player, data->map_pars);
	if(data->player->moving_down)
		buttons_s(data->player, data->map_pars);
	if(data->player->moving_up)
		buttons_w(data->player, data->map_pars);
	check_doors(data);
}

int render(t_data *data)
{
	clear_window(data->win);
	drawSkybox(data);
	drawRays2D(data);
	player_position(data);
	update_doors(data, 0.016);
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