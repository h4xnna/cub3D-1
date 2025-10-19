/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:51:22 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/19 14:22:01 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

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
		ray_x += data->raycast.rayDirX;
		ray_y += data->raycast.rayDirY;
		my_mlx_pixel_put(&data->win, ray_x, ray_y, 0xFF0000);
	}
	
}

void drawRays2D(t_data *data )
{
	int x = 0;

	while( x <= WIDTH)
    {
		data->raycast.cameraX = 2 * x / (double)WIDTH - 1;
		data->raycast.rayDirX = data->player.pdirx + data->player.planeX * data->raycast.cameraX;
		data->raycast.rayDirY = data->player.pdiry + data->player.planeY * data->raycast.cameraX;

		if (data->raycast.rayDirX == 0)
			data->raycast.rayDirX = 0.001;
		if (data->raycast.rayDirY == 0)
			data->raycast.rayDirY = 0.001;
		
		
		data->raycast.mapX = (int)data->player.px;
		data->raycast.mapY = (int)data->player.py;

		data->raycast.deltaDistX = fabs(1 / data->raycast.rayDirX);
		data->raycast.deltaDistY = fabs(1 / data->raycast.rayDirY);


		if (data->raycast.rayDirX < 0)
		{
			data->raycast.stepX = -1;
			data->raycast.sideDistX = (data->player.px - data->raycast.mapX) * data->raycast.deltaDistX;
		}
		else
		{
			data->raycast.stepX = 1;
			data->raycast.sideDistX = (data->raycast.mapX + 1.0 - data->player.px) * data->raycast.deltaDistX;
		}

		if (data->raycast.rayDirY < 0)
		{
			data->raycast.stepY = -1;
			data->raycast.sideDistY = (data->player.py - data->raycast.mapY) * data->raycast.deltaDistY;
		}
		else
		{
			data->raycast.stepY = 1;
			data->raycast.sideDistY = (data->raycast.mapY + 1.0 - data->player.py) * data->raycast.deltaDistY;
		}


		data->raycast.hit = 0;

		while (data->raycast.hit == 0)
		{
			if (data->raycast.sideDistX < data->raycast.sideDistY)
			{
				data->raycast.sideDistX += data->raycast.deltaDistX;
				data->raycast.mapX += data->raycast.stepX;
				data->raycast.side = 0;
			}
			else
			{
				data->raycast.sideDistY += data->raycast.deltaDistY;
				data->raycast.mapY += data->raycast.stepY;
				data->raycast.side = 1;
			}
			if (data->raycast.mapX >= 0 && data->raycast.mapY >= 0 && data->map_pars.map[data->raycast.mapY] && data->map_pars.map[data->raycast.mapY][data->raycast.mapX]
				&& data->map_pars.map[data->raycast.mapY][data->raycast.mapX] == '1')	
				data->raycast.hit = 1;

		}

		// draw_line(cameraX, rayDirY, data);

		if(data->raycast.side == 0)
			data->raycast.perpWallDist = (data->raycast.sideDistX - data->raycast.deltaDistX);
    	else
			data->raycast.perpWallDist = (data->raycast.sideDistY - data->raycast.deltaDistY);


		data->raycast.lineHeight = (int)(HEIGHT / data->raycast.perpWallDist);

		data->raycast.drawStart = -data->raycast.lineHeight / 2 + HEIGHT / 2;
		if(data->raycast.drawStart < 0)
			data->raycast.drawStart = 0;

		data->raycast.drawEnd = data->raycast.lineHeight / 2 + HEIGHT / 2;
		if(data->raycast.drawEnd >= HEIGHT)
			data->raycast.drawEnd = HEIGHT - 1;

		while(data->raycast.drawStart <= data->raycast.drawEnd)
		{
			if (data->raycast.side == 0)
				my_mlx_pixel_put( &data->win, x, data->raycast.drawStart, 0xB82010);
			else
				my_mlx_pixel_put( &data->win, x, data->raycast.drawStart, 0x87180C);
			data->raycast.drawStart++;
		}
		x++;
	}
	draw_map(data);
	draw_square(data, (data->player.px * SIZE_SQUARE),(data->player.py * SIZE_SQUARE), NOIR, SIZE_SQUARE/ 3);
	mlx_put_image_to_window(data->win.mlx, data->win.win, data->win.img, 0, 0);
}
