/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:19:33 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/28 14:04:19 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	x_to_0(t_map_pars *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->map[y])
	{
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'X')
				map->map[y][x] = '0';
			x++;
		}
		x = 0;
		y++;
	}
}
void	draw_square(t_data *data, int x, int y, int color, int square_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < square_size)
	{
		j = 0;
		while (j < square_size)
		{
			my_mlx_pixel_put(&data->win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

#define HALF_MINIMAP (MINIMAP_RADIUS / 2)

void draw_map(t_data *data)
{
    int px = data->player.px;
    int py = data->player.py;

    for (int yCases = 0; yCases < MINIMAP_RADIUS; yCases++)
    {
        for (int xCases = 0; xCases < MINIMAP_RADIUS; xCases++)
        {
            if ((yCases == 0 && xCases == 0) ||
                (yCases == 0 && xCases == MINIMAP_RADIUS - 1) ||
                (yCases == MINIMAP_RADIUS - 1 && xCases == 0) ||
                (yCases == MINIMAP_RADIUS - 1 && xCases == MINIMAP_RADIUS - 1))
                continue;

            int map_y = py + (yCases - HALF_MINIMAP);
            int map_x = px + (xCases - HALF_MINIMAP);

            char tile = 0;
            if ((map_y >= 0 && map_y < data->map_pars.height) &&
                map_x >= 0 &&
                data->map_pars.map[map_y] &&
                data->map_pars.map[map_y][map_x])
                tile = data->map_pars.map[map_y][map_x];

            int color;
            if (tile == '1')
                color = 0xAF0000;
            else if (tile == '0')
                color = BLANC;
            else
                color = 0x000000;

            int draw_x = xCases * SIZE_SQUARE + SIZE_SQUARE;
            int draw_y = yCases * SIZE_SQUARE + SIZE_SQUARE;

            draw_square(data, draw_x, draw_y, color, SIZE_SQUARE);
        }
    }

    int player_x = HALF_MINIMAP * SIZE_SQUARE + SIZE_SQUARE / 4 + SIZE_SQUARE;
    int player_y = HALF_MINIMAP * SIZE_SQUARE + SIZE_SQUARE / 4 + SIZE_SQUARE;
    draw_square(data, player_x, player_y, ROUGE, SIZE_SQUARE / 2);
}

int is_wall(t_data *data, float ray_x, float ray_y)
{
	if (data->map_pars.map[(int)(ray_y / SIZE_SQUARE)][(int)(ray_x / SIZE_SQUARE)]
			&& data->map_pars.map[(int)(ray_y / SIZE_SQUARE)][(int)(ray_x / SIZE_SQUARE)] == '1')
			return (1);
	return (0);
}

void draw_line(t_data *data)
{
	float ray_x = data->player.px * SIZE_SQUARE;
	float ray_y = data->player.py * SIZE_SQUARE;
	
	while (!is_wall(data, ray_x, ray_y))
	{
		ray_x += data->raycast.raydirx;
		ray_y += data->raycast.raydiry;
		my_mlx_pixel_put(&data->win, ray_x, ray_y, 0xFF0000);
	}
	
}