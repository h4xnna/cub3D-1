/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:43:22 by hmimouni          #+#    #+#             */
/*   Updated: 2025/12/29 18:13:00 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	buttons_a(t_player *player, t_map_pars *map)
{
	double	strafe_x;
	double	strafe_y;

	strafe_x = player->pdiry;
	strafe_y = -player->pdirx;
	if (map->map[(int)player->py][(int)(player->px + strafe_x * 0.2)] == '0')
		player->px += strafe_x * 0.1;
	if (map->map[(int)(player->py + strafe_y * 0.2)][(int)player->px] == '0')
		player->py += strafe_y * 0.1;
}

void	buttons_d(t_player *player, t_map_pars *map)
{
	double	strafe_x;
	double	strafe_y;

	strafe_x = -player->pdiry;
	strafe_y = player->pdirx;
	if (map->map[(int)player->py][(int)(player->px + strafe_x * 0.2)] == '0')
		player->px += strafe_x * 0.1;
	if (map->map[(int)(player->py + strafe_y * 0.2)][(int)player->px] == '0')
		player->py += strafe_y * 0.1;
}

void	buttons_w(t_player *player, t_map_pars *map)
{
	if ((map->map[(int)player->py][(int)(player->px + player->pdirx
			* 0.2)]) == '0')
		player->px += player->pdirx * 0.1;
	if (map->map[(int)(player->py + player->pdiry
			* 0.2)][(int)(player->px)] == '0')
		player->py += player->pdiry * 0.1;
}

void	buttons_s(t_player *player, t_map_pars *map)
{
	if ((map->map[(int)player->py][(int)(player->px - player->pdirx
			* 0.2)]) == '0')
		player->px -= player->pdirx * 0.1;
	if (map->map[(int)(player->py - player->pdiry
			* 0.2)][(int)(player->px)] == '0')
		player->py -= player->pdiry * 0.1;
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == A_KEY)
		buttons_a(data->player, data->map_pars);
	if (keycode == D_KEY)
		buttons_d(data->player, data->map_pars);
	if (keycode == S_KEY)
		buttons_s(data->player, data->map_pars);
	if (keycode == W_KEY)
		buttons_w(data->player, data->map_pars);
	if (keycode == 65307)
		clean_exit(data);
	if (keycode == 65363)
		move_camera_right(data);
	if (keycode == 65361)
		move_camera_left(data);
	return (0);
}