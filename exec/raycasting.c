/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:51:22 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/08 16:33:32 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void draw_line(t_data *data, float angle)
{
	float cosi = cos(angle);
	float sinu = sin(angle);

	float ray_x = data->player.px * SIZE_SQUARE;
	float ray_y = data->player.py * SIZE_SQUARE;
	
	while (!is_wall(data, ray_x, ray_y))
	{
		ray_x += cosi;
		ray_y += sinu;
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, ray_x, ray_y, 0xFF0000);
	}
	
}

void drawRays2D(t_data *data )
{
	int i = 0;
	// player.pa = pi/2
	float angle = data->player.pa;
	while(i < 720 / 6)
	{
		draw_line(data, angle);
		angle += 0.0125;
		i++;
	}
}
