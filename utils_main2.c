/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:54:11 by hmimouni          #+#    #+#             */
/*   Updated: 2025/11/09 19:49:54 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double get_time_seconds(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (t.tv_sec + t.tv_usec / 1000000.0);
}

void rotate_player(t_data *data, int mouse_x)
{
	static double current_speed = 0.0;
 
	double max_speed = 0.15;
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

static void	update_doors(t_data	*data, double delta_time)
{
	t_door	*door;

	door = data->doors;
	while (door)
	{
		if (sqrt(pow(data->player->px - (door->x + 0.5), 2) + pow(data->player->py - (door->y + 0.5), 2)) < sqrt(2))
		{
			if (door->opening >= 0.0 || !door->opened)
				door->opened = 1;
		}
		else
		{
			data->map_pars->map[door->y][door->x] = 'D';
			door->opened = -1;
		}
		if (door->opened == 1 && door->opening < 1.0)
			door->opening += delta_time * 0.8;
		else if (door->opened == -1 && door->opening > 0.0)
			door->opening += delta_time * -0.8;
		if (door->opening >= 1.0)
		{
			door->opening = 1.0;
			data->map_pars->map[door->y][door->x] = '0';
		}
		if (door->opening <= 0.0)
			door->opening = 0.0;
		// printf("%d : %f\n", door->opened, door->opening);
		door = door->next;
	}
}

static void player_position(t_data *data)
{
	static bool	exited = 0;
	if (data->player->moving_left && !exited)
		buttons_a(data->player, data->map_pars);
	if (data->player->moving_right && !exited)
		buttons_d(data->player, data->map_pars);
	if(data->player->moving_down && !exited)
		buttons_s(data->player, data->map_pars);
	if(data->player->moving_up && !exited)
		buttons_w(data->player, data->map_pars);
	if(data->map_pars->map[(int)data->player->py][(int)(data->player->px)] == 'L')
		exited = 1;
	if (exited == 1)
	{
		if ((data->player->pitch + 20) > 1080)
			data->player->pitch = 1080;
		else
			data->player->pitch -= 20;
	}
}

int render(t_data *data)
{
    static double last_time = 0;
    double current_time = get_time_seconds();
	
	data->player->delta_time = current_time - last_time;
    last_time = current_time;
	
    double fps = 1.0 / data->player->delta_time;

    clear_window(data->win);
    drawSkybox(data);
    drawRays2D(data);
    player_position(data);
	rotate_player(data, data->player->mouse_x);
    update_doors(data, data->player->delta_time);
    mlx_string_put(data->win->mlx, data->win->win, WIDTH - 20, 20, 0xFFFFFF, ft_itoa((int)fps));

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