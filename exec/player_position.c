/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:51:35 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/18 18:04:03 by hmimouni         ###   ########.fr       */
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

int rgb_to_hex_int(int *rgb)
{
    if (!rgb)
        error_message("RGB pointer is NULL.");

    int r = rgb[0];
    int g = rgb[1];
    int b = rgb[2];

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        error_message("Valeur RGB invalide.");

    return ((r << 16) | (g << 8) | b);
}

void split_win(t_data *data)
{
	int x;
	int y;
	int colors_ceiling = rgb_to_hex_int(data->map_info.ceiling);
	int colors_floor = rgb_to_hex_int(data->map_info.floor);
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, colors_ceiling);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, colors_floor);
			x++;
		}
		y++;
	}
}