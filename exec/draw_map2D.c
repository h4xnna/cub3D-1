/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:19:33 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/21 21:39:10 by pacda-si         ###   ########.fr       */
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

void draw_map(t_data *data)
{
    int px = data->player.px;
    int py = data->player.py;

    int yCases = -MINIMAP_RADIUS;
    while (yCases <= MINIMAP_RADIUS)
    {
        int xCases = -MINIMAP_RADIUS;
        while (xCases <= MINIMAP_RADIUS)
        {
            double dist = sqrt(xCases * xCases + yCases * yCases);
            if (dist <= MINIMAP_RADIUS)
            {
                int map_y = py + yCases;
                int map_x = px + xCases;

                if ((map_y >= 0 && map_y < data->map_pars.height) &&
                    map_x >= 0 &&
                    data->map_pars.map[map_y] &&
                    data->map_pars.map[map_y][map_x])
                {
                    int color;
                    char tile = data->map_pars.map[map_y][map_x];

                    if (tile == '1')
                        color = TEAL;
                    else if (tile == '0')
                        color = BLANC;
                    else
                        color = 0x000000;

                    int draw_x = (xCases + MINIMAP_RADIUS) * SIZE_SQUARE;
                    int draw_y = (yCases + MINIMAP_RADIUS) * SIZE_SQUARE;

                    draw_square(data, draw_x, draw_y, color, SIZE_SQUARE);
                }
            }
            xCases++;
        }
        yCases++;
    }

    int player_x = MINIMAP_RADIUS * SIZE_SQUARE + SIZE_SQUARE / 4;
    int player_y = MINIMAP_RADIUS * SIZE_SQUARE + SIZE_SQUARE / 4;
    draw_square(data, player_x, player_y, ROUGE, SIZE_SQUARE / 2);
}

// void draw_map(t_data *data)
// {
// 	int y = data->player.py - 1;
// 	int x = data->player.px - 1;

// 	int yCases = 0;
// 	int xCases;

// 	while (data->map_pars.map[y + yCases] && yCases < 3)
// 	{
// 		xCases = 0;
// 		while (data->map_pars.map[y + yCases][x + xCases] && xCases < 3) 
// 		{
// 			if (data->map_pars.map[y + yCases][x + xCases] == '1')
// 				draw_square(data, xCases * SIZE_SQUARE, yCases * SIZE_SQUARE, TEAL, SIZE_SQUARE);
// 			else if (data->map_pars.map[y][x + xCases] == '0')
// 				draw_square(data, xCases * SIZE_SQUARE, yCases * SIZE_SQUARE, BLANC, SIZE_SQUARE);
// 			xCases++;
// 		}
// 		yCases++;
// 	}
// }

