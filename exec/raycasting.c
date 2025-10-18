/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:51:22 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/18 14:49:13 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

// void drawRays2D(t_data *data)
// {
// 	int r = 0;
// 	int mx;
// 	int mp;
// 	int my;
// 	float rx;
// 	float ry;
// 	float ra;
// 	float xo;
// 	float yo;
// 	ra = data->player.pa;
// 	while(r < 1)
// 	{
// 		int dof = 0;
// 		float aTan = -1/tan(ra);
// 		if(ra > PI)
// 		{
// 			ry = (((int)data->player.py >> 6) << 6) -0.0001;
// 			rx=(data->player.py-ra)*aTan+data->player.px;
// 			yo=-64;
// 			xo=-yo*aTan;
// 		}
// 		if(ra < PI)
// 		{
// 			ry = (((int)data->player.py >> 6) << 6) +64;
// 			rx=(data->player.py-ra)*aTan+data->player.px;
// 			yo=64;
// 			xo=-yo*aTan;
// 		}
// 		if(ra == 0|| ra == PI)
// 		{
// 			rx = data->player.px;
// 			ry = data->player.py;
// 			dof = 8;
// 		}
// 		while(dof < 8)
// 		{
// 			mx =(int)(rx)>>6;
// 			my = (int)(ry) >> 6;
// 			mp=my*mapX+mx;
// 			if(mp<mapX*mapY && map[mp])
// 		}
// 		r++;
// 	}
// }

int is_wall(t_data *data, float ray_x, float ray_y)
{
	if (data->map_pars.map[(int)(ray_y / SIZE_SQUARE)][(int)(ray_x / SIZE_SQUARE)]
			&& data->map_pars.map[(int)(ray_y / SIZE_SQUARE)][(int)(ray_x / SIZE_SQUARE)] == '1')
			return (1);
	return (0);
}

void draw_line(double rayDirX, double rayDirY, t_data *data)
{
	float ray_x = data->player.px * SIZE_SQUARE;
	float ray_y = data->player.py * SIZE_SQUARE;
	
	while (!is_wall(data, ray_x, ray_y))
	{
		ray_x += rayDirX;
		ray_y += rayDirY;
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, ray_x, ray_y, 0xFF0000);
	}
	
}

void drawRays2D(t_data *data )
{
	double cameraX;
	double rayDirX;
	double rayDirY;

	int mapX;
	int mapY;
	
	double sideDistX;
	double sideDistY;

	double deltaDistX;
	double deltaDistY;

	double perpWallDist;

	int stepX;
	int stepY;

	int hit;
	int side;
	int x = 0;

	int lineHeight;
	int drawStart;
	int drawEnd;

	while( x <= WIDTH)
    {
		cameraX = 2 * x / (double)WIDTH - 1;
		rayDirX = data->player.pdirx + data->player.planeX * cameraX;
		rayDirY = data->player.pdiry + data->player.planeY * cameraX;

		if (rayDirX == 0)
			rayDirX = 0.001;
		if (rayDirY == 0)
			rayDirY = 0.001;
		
		
		mapX = (int)data->player.px;
		mapY = (int)data->player.py;

		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);


		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->player.px - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->player.px) * deltaDistX;
		}

		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->player.py - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->player.py) * deltaDistY;
		}


		hit = 0;

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (mapX >= 0 && mapY >= 0 && data->map_pars.map[mapY] && data->map_pars.map[mapY][mapX]
				&& data->map_pars.map[mapY][mapX] == '1')	
				hit = 1;

		}

		// draw_line(cameraX, rayDirY, data);

		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
    	else
			perpWallDist = (sideDistY - deltaDistY);


		lineHeight = (int)(HEIGHT / perpWallDist);

		drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;

		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		while(drawStart <= drawEnd)
		{
			if (side == 0)
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, drawStart, 0x00FF00);
			else
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, drawStart, 0x00FF00 / 3);
			drawStart++;
		}
		x++;
	}
	draw_map(data);
	draw_square(data, (data->player.px * SIZE_SQUARE),(data->player.py * SIZE_SQUARE), NOIR, SIZE_SQUARE/ 3);
}
