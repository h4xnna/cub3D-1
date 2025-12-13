/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:43:22 by hmimouni          #+#    #+#             */
/*   Updated: 2025/12/13 11:50:25 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_walkable(char c)
{
	char	walkalbles[3]= "0L";
	int		i;

	i = 0;
	while (walkalbles[i])
	{
		if (c == walkalbles[i])
			return (true);
		i++;
	}
	return (false);
}

void	buttons_a(t_player *player, t_map_pars *map)
{
	double	strafe_x;
	double	strafe_y;

	strafe_x = player->pdiry;
	strafe_y = -player->pdirx;
	if (is_walkable(map->map[(int)player->py][(int)(player->px + strafe_x
			* 0.2)]))
		player->px += strafe_x * MOVE_SPEED * player->delta_time;
	if (is_walkable(map->map[(int)(player->py + strafe_y
				* 0.2)][(int)player->px]))
		player->py += strafe_y * MOVE_SPEED * player->delta_time;
}

void	buttons_d(t_player *player, t_map_pars *map)
{
	double	strafe_x;
	double	strafe_y;

	strafe_x = -player->pdiry;
	strafe_y = player->pdirx;
	if (is_walkable(map->map[(int)player->py][(int)(player->px + strafe_x
			* 0.2)]))
		player->px += strafe_x * MOVE_SPEED * player->delta_time;
	if (is_walkable(map->map[(int)(player->py + strafe_y
				* 0.2)][(int)player->px]))
		player->py += strafe_y * MOVE_SPEED * player->delta_time;
}

void	buttons_w(t_player *player, t_map_pars *map)
{
	if (is_walkable(map->map[(int)player->py][(int)(player->px + player->pdirx
			* 0.2)]))
		player->px += player->pdirx * MOVE_SPEED * player->delta_time;
	if (is_walkable(map->map[(int)(player->py + player->pdiry
				* 0.2)][(int)(player->px)]))
		player->py += player->pdiry * MOVE_SPEED * player->delta_time;
}

void	buttons_s(t_player *player, t_map_pars *map)
{
	if (is_walkable(map->map[(int)player->py][(int)(player->px - player->pdirx
			* 0.2)]))
		player->px -= player->pdirx * MOVE_SPEED * player->delta_time;
	if (is_walkable(map->map[(int)(player->py - player->pdiry
				* 0.2)][(int)(player->px)]))
		player->py -= player->pdiry * MOVE_SPEED * player->delta_time;
}
