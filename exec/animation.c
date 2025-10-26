/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:46:58 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/26 14:51:19 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Normalisation d'un vecteur 2D
void normalize_vector(double *x, double *y)
{
    double length = sqrt((*x) * (*x) + (*y) * (*y));
    if (length != 0)
    {
        *x /= length;
        *y /= length;
    }
}

void left_key(t_data *data)
{
	double oldDirX = data->player.pdirx;
		data->player.pdirx = data->player.pdirx * cos(-ROTSPEED) - data->player.pdiry * sin(-ROTSPEED);
		data->player.pdiry = oldDirX * sin(-ROTSPEED) + data->player.pdiry * cos(-ROTSPEED);
		double oldplanex = data->player.planex;
		data->player.planex = data->player.planex * cos(-ROTSPEED) - data->player.planey * sin(-ROTSPEED);
		data->player.planey = oldplanex * sin(-ROTSPEED) + data->player.planey * cos(-ROTSPEED);
		normalize_vector(&data->player.pdirx, &data->player.pdiry);
		normalize_vector(&data->player.planex, &data->player.planey);
}
void right_key(t_data *data)
{
	double oldDirX = data->player.pdirx;
		data->player.pdirx = data->player.pdirx * cos(ROTSPEED) - data->player.pdiry * sin(ROTSPEED);
		data->player.pdiry = oldDirX * sin(ROTSPEED) + data->player.pdiry * cos(ROTSPEED);
		double oldplanex = data->player.planex;
		data->player.planex = data->player.planex * cos(ROTSPEED) - data->player.planey * sin(ROTSPEED);
		data->player.planey = oldplanex * sin(ROTSPEED) + data->player.planey * cos(ROTSPEED);
		normalize_vector(&data->player.pdirx, &data->player.pdiry);
		normalize_vector(&data->player.planex, &data->player.planey);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == A_KEY)
		buttons_a(&data->player, &data->map_pars);
	if (keycode == D_KEY)
		buttons_d(&data->player, &data->map_pars);
	if(keycode == S_KEY)
		buttons_s(&data->player, &data->map_pars);
	if(keycode == W_KEY)
		buttons_w(&data->player, &data->map_pars);
	if (keycode == 65307)
		clean_exit(data);
	if (keycode == 65361) // fleche guache
		left_key(data);
	if (keycode == 65363) // fleche droite
		right_key(data);
	return (0);
}