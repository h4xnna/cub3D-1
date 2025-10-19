/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:19:33 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/19 12:41:44 by hmimouni         ###   ########.fr       */
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
	int y = 0;
	int x;

	while (data->map_pars.map[y])
	{
		x = 0;
		while (data->map_pars.map[y][x]) 
		{
			if (data->map_pars.map[y][x] == '1')
				draw_square(data, x * SIZE_SQUARE, y * SIZE_SQUARE, TEAL, SIZE_SQUARE);
			else if (data->map_pars.map[y][x] == '0')
				draw_square(data, x * SIZE_SQUARE, y * SIZE_SQUARE, BLANC, SIZE_SQUARE);
			x++;
		}
		y++;
	}
}

