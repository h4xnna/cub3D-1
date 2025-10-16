/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:43:22 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/16 11:10:27 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	buttons_a(t_player *player, t_map_pars *map)
{
	// (void)map;
	// player->pa -= 0.05;
	// if (player->pa < 0)
	// 	player->pa += 2 * PI;
	// player->pdx = cos(player->pa) * 5;
	// player->pdy = sin(player->pa) * 5;
	if (map->map[(int)player->py][(int)(player->px -1)]
			&& map->map[(int)player->py][(int)(player->px -1)] != '1')
	player->px -=1;
}

void	buttons_d(t_player *player, t_map_pars *map)
{
	(void)map;
	// player->pa -= 0.05;
	// if (player->pa > 2 * PI)
	// 	player->pa -= 2 * PI;
	// player->pdx = cos(player->pa) * 5;
	// player->pdy = sin(player->pa) * 5;
	player->px += player->pdirx;
	// if (map->map[(int)player->py][(int)(player->px + 1)]
	// 		&& map->map[(int)player->py][(int)(player->px + 1)] != '1')
	// 	player->px += 1;
}
void	buttons_w(t_player *player, t_map_pars *map)
{
	// (void)map;
	// player->px += player->pdx;
	// player->py += player->pdy;
	if (map->map[(int)(player->py - 1)][(int)(player->px)]
			&& map->map[(int)(player->py - 1)][(int)(player->px)] != '1')
		player->py -= 1;
}

void	buttons_s(t_player *player, t_map_pars *map)
{
	// (void)map;
	// player->px -= player->pdx;
	// player->py -= player->pdy;
	if (map->map[(int)(player->py + 1)][(int)(player->px)]
			&& map->map[(int)(player->py + 1)][(int)(player->px)] != '1')
		player->py += 1;
}
