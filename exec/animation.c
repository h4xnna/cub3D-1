/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:46:58 by hmimouni          #+#    #+#             */
/*   Updated: 2025/11/06 11:39:33 by pacda-si         ###   ########.fr       */
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

int	key_press(int keycode, t_data *data)
{
	if (keycode == A_KEY)
		buttons_a(data->player, data->map_pars);
	if (keycode == D_KEY)
		buttons_d(data->player, data->map_pars);
	if(keycode == S_KEY)
		buttons_s(data->player, data->map_pars);
	if(keycode == W_KEY)
		buttons_w(data->player, data->map_pars);
	if (keycode == 65307)
		clean_exit(data);
	if (keycode == 65363)
		move_camera_right(data);
	if (keycode == 65361)
		move_camera_left(data);
	return (0);
}
