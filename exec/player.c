/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:51:35 by hmimouni          #+#    #+#             */
/*   Updated: 2025/12/29 18:06:56 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->pdiry = -1;
		player->planex = 0.66;
		player->planey = 0;
	}
	else if (direction == 'S')
	{
		player->pdiry = 1;
		player->planex = -0.66;
		player->planey = 0;
	}
	else if (direction == 'E')
	{
		player->pdirx = 1;
		player->planex = 0;
		player->planey = 0.66;
	}
	else if (direction == 'W')
	{
		player->pdirx = -1;
		player->planex = 0;
		player->planey = -0.66;
	}
}

int	rgb_to_hex_int(t_data *data, int *rgb)
{
	int	r;
	int	g;
	int	b;

	if (!rgb)
	{
		error_message(" RGB pointer is NULL.");
		clean_exit(data);
	}
	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		error_message("Valeur RGB invalide.");
		clean_exit(data);
	}
	return ((r << 16) | (g << 8) | b);
}
