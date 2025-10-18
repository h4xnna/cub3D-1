/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:51:35 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/18 17:55:35 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_player_direction(t_player *player, char direction)
{
    if (direction == 'N')
    {
        player->pdirx = 0;
        player->pdiry = -1;
        player->planeX = 0.66;
        player->planeY = 0;
    }
    else if (direction == 'S')
    {
        player->pdirx = 0;
        player->pdiry = 1;
        player->planeX = -0.66;
        player->planeY = 0;
    }
    else if (direction == 'E')
    {
        player->pdirx = 1;
        player->pdiry = 0;
        player->planeX = 0;
        player->planeY = 0.66;
    }
    else if (direction == 'W')
    {
        player->pdirx = -1;
        player->pdiry = 0;
        player->planeX = 0;
        player->planeY = -0.66;
    }
}

// int    rgb_to_hex_int(char *color)
// {
//     int        rgb[3];
//     char    **rgb_tab;

//     rgb_tab = ft_split(color, ',');
//     if (!rgb_tab)
//         end_game("Memory allocation failed.\n");
//     rgb[0] = (int)ft_atol(rgb_tab[0]);
//     rgb[1] = (int)ft_atol(rgb_tab[1]);
//     rgb[2] = (int)ft_atol(rgb_tab[2]);
//     return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
// }
void split_win(t_data *data)
{
	int x;
	int y;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, rgb_to_hex_int(data->map_info->));
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, TEAL);
			x++;
		}
		y++;
	}
}