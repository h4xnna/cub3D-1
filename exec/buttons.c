/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:43:22 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/18 15:37:34 by hmimouni         ###   ########.fr       */
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
	if (map->map[(int)player->py][(int)(player->px -0.1)]
			&& map->map[(int)player->py][(int)(player->px -0.1)] != '1')
	player->px -= player->pdirx * 0.1;
}

void	buttons_d(t_player *player, t_map_pars *map)
{
	(void)map;
	if((map->map[(int)player->py][(int)(player->px + player->pdirx *0.1)]) == '0')
		 player->px += player->pdirx * 0.1;
     if(map->map[(int)(player->py + player->pdiry *0.1)][(int)(player->px)] == '0') 
	 	player->py += player->pdiry * 0.1;
}
void	buttons_w(t_player *player, t_map_pars *map)
{
	// (void)map;

	if((map->map[(int)player->py][(int)(player->px + player->pdirx *0.1)]) == '0')
		 player->px += player->pdirx * 0.1;
     if(map->map[(int)(player->py + player->pdiry *0.1)][(int)(player->px)] == '0') 
	 	player->py += player->pdiry * 0.1;
}

void	buttons_s(t_player *player, t_map_pars *map)
{
		if((map->map[(int)player->py][(int)(player->px + player->pdirx *0.1)]) == '0')
		 player->px -= player->pdirx *0.1;
     if(map->map[(int)(player->py + player->pdiry *0.1)][(int)(player->px)] == '0') 
	 	player->py -= player->pdiry *0.1;
}
