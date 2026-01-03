/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:46:58 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/03 17:29:55 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	reset_all_animations(t_data *data)
{
	if (data->knife_anim->playing)
	{
		data->knife_anim->playing = 0;
		data->knife_anim->current_frame = 0;
	}
	if (data->deploy_anim->playing)
	{
		data->deploy_anim->playing = 0;
		data->deploy_anim->current_frame = 0;
	}
	if (data->lmb_anim->playing)
	{
		data->lmb_anim->playing = 0;
		data->lmb_anim->current_frame = 0;
	}
	if (data->rmb_anim->playing)
	{
		data->rmb_anim->playing = 0;
		data->rmb_anim->current_frame = 0;
	}
}

void	normalize_vector(double *x, double *y)
{
	double	length;

	length = sqrt((*x) * (*x) + (*y) * (*y));
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
	if (keycode == S_KEY)
		data->player->moving_down = false;
	if (keycode == W_KEY)
		data->player->moving_up = false;
	return (SUCCESS);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == A_KEY)
		data->player->moving_left = true;
	if (keycode == D_KEY)
		data->player->moving_right = true;
	if (keycode == S_KEY)
		data->player->moving_down = true;
	if (keycode == W_KEY)
		data->player->moving_up = true;
	if (keycode == 65307)
		clean_exit(data);
	if (keycode == 65363)
		data->player->rotate_right = true;
	if (keycode == 65361)
		data->player->rotate_left = true;
	if (data->player->show_knife && keycode == 121)
	{
		reset_all_animations(data);
		data->knife_anim->playing = 1;
	}
	if (keycode == 51)
	{
		data->player->show_knife = true;
		reset_all_animations(data);
		data->deploy_anim->playing = 1;
	}
	if (keycode == 50 || keycode == 49)
	{
		data->player->show_knife = false;
		reset_all_animations(data);
	}
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == 1 && data->player->show_knife)
	{
		reset_all_animations(data);
		data->lmb_anim->playing = 1;
	}
	if (keycode == 3 && data->player->show_knife)
	{
		reset_all_animations(data);
		data->rmb_anim->playing = 1;
	}
	return (0);
}

int	mouse_info(int x, int y, t_data *data)
{
	data->player->mouse_x = x;
	data->player->mouse_y = y;
	return (0);
}