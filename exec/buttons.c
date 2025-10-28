/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:43:22 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/28 13:01:29 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	buttons_a(t_player *player, t_map_pars *map)
{
		double strafe_x = player->pdiry;
		double strafe_y = -player->pdirx;
		if (map->map[(int)player->py][(int)(player->px + strafe_x
				* 0.2)] == '0')
			player->px += strafe_x * 0.05;
		if (map->map[(int)(player->py + strafe_y * 0.2)][(int)player->px] == '0')
			player->py += strafe_y * 0.05;
}

void	buttons_d(t_player *player, t_map_pars *map)
{
		double strafe_x = -player->pdiry;
		double strafe_y = player->pdirx;
		if (map->map[(int)player->py][(int)(player->px + strafe_x
				* 0.2)] == '0')
			player->px += strafe_x * 0.05;
		if (map->map[(int)(player->py + strafe_y * 0.2)][(int)player->px] == '0')
			player->py += strafe_y * 0.05;
	}

void	buttons_w(t_player *player, t_map_pars *map)
{
	if ((map->map[(int)player->py][(int)(player->px + player->pdirx
				* 0.2)]) == '0')
		player->px += player->pdirx * 0.05;
	if (map->map[(int)(player->py + player->pdiry
			* 0.2)][(int)(player->px)] == '0')
		player->py += player->pdiry * 0.05;
}

void	buttons_s(t_player *player, t_map_pars *map)
{
	if ((map->map[(int)player->py][(int)(player->px + player->pdirx
				* -0.2)]) == '0')
		player->px -= player->pdirx * 0.05;
	if (map->map[(int)(player->py + player->pdiry
			* -0.2)][(int)(player->px)] == '0')
		player->py -= player->pdiry * 0.05;
}
