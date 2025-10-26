/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:19:33 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/26 14:34:39 by hmimouni         ###   ########.fr       */
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