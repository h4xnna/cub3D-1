/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:43:22 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/19 11:30:41 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	buttons_a(t_player *player, t_map_pars *map)
{
		double strafe_x = player->pdiry;
		double strafe_y = -player->pdirx;
		if (map->map[(int)player->py][(int)(player->px + strafe_x
				* 0.1)] == '0')
			player->px += strafe_x * 0.1;
		if (map->map[(int)(player->py + strafe_y * 0.1)][(int)player->px] == '0')
			player->py += strafe_y * 0.1;
}

void	buttons_d(t_player *player, t_map_pars *map)
{
		double strafe_x = -player->pdiry;
		double strafe_y = player->pdirx;
		if (map->map[(int)player->py][(int)(player->px + strafe_x
				* 0.1)] == '0')
			player->px += strafe_x * 0.1;
		if (map->map[(int)(player->py + strafe_y * 0.1)][(int)player->px] == '0')
			player->py += strafe_y * 0.1;
	}

void	buttons_w(t_player *player, t_map_pars *map)
{
	if ((map->map[(int)player->py][(int)(player->px + player->pdirx
				* 0.1)]) == '0')
		player->px += player->pdirx * 0.1;
	if (map->map[(int)(player->py + player->pdiry
			* 0.1)][(int)(player->px)] == '0')
		player->py += player->pdiry * 0.1;
}

void	buttons_s(t_player *player, t_map_pars *map)
{
	if ((map->map[(int)player->py][(int)(player->px + player->pdirx
				* 0.1)]) == '0')
		player->px -= player->pdirx * 0.1;
	if (map->map[(int)(player->py + player->pdiry
			* 0.1)][(int)(player->px)] == '0')
		player->py -= player->pdiry * 0.1;
}
