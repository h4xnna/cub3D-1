/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:46:58 by hmimouni          #+#    #+#             */
/*   Updated: 2025/11/05 19:17:47 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void normalize_vector(double *x, double *y)
{
    double length = sqrt((*x) * (*x) + (*y) * (*y));
    if (length != 0)
    {
        *x /= length;
        *y /= length;
    }
}


int	key_release(int keycode, t_data *data)
{
	if (keycode == 65363)
		data->player->rotate_right = false;
	if (keycode == 65361)
		data->player->rotate_left = false;
	if (keycode == A_KEY)
		data->player->moving_left = false;
	if (keycode == D_KEY)
		data->player->moving_right = false;
	if(keycode == S_KEY)
		data->player->moving_down = false;
	if(keycode == W_KEY)
		data->player->moving_up = false;

	return(SUCCESS);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == A_KEY)
		data->player->moving_left = true;
	if (keycode == D_KEY)
		data->player->moving_right = true;
	if(keycode == S_KEY)
		data->player->moving_down = true;
	if(keycode == W_KEY)
		data->player->moving_up = true;
	if (keycode == 65307)
	{
		mlx_destroy_window(data->win->mlx, data->win->win);
		mlx_clear_window(data->win->mlx, data->win->win);
		exit(1);
	}
	if (keycode == 65363)
		data->player->rotate_right = true;
	if (keycode == 65361)
		data->player->rotate_left = true;
	return (0);
}

int mouse_info(int x, int y, t_data *data)
{
	data->player->rotate_speed = data->player->sensitivity * (x - (WIDTH / 2));

	(void)y;
	if (x > WIDTH / 2)
	{
		data->player->rotate_right = true;
		if (data->player->rotate_left)
			data->player->rotate_left = false;
	}
	else if (x < WIDTH / 2)
	{
		data->player->rotate_left = true;
		if (data->player->rotate_right)
			data->player->rotate_right = false;
	}
	else
	{
		data->player->rotate_left = false;
		data->player->rotate_right = false;
	}
	return (0);
}