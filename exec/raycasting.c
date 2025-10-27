/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:51:22 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/26 17:28:13 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void drawRays2D(t_data *data )
// {
// 	int x = 0;

// 	while( x <= WIDTH)
//     {
// 		data->raycast.camerax = 2 * x / (double)WIDTH - 1;
// 		data->raycast.raydirx = data->player.pdirx + data->player.planex * data->raycast.camerax;
// 		data->raycast.raydiry = data->player.pdiry + data->player.planey * data->raycast.camerax;

// 		if (data->raycast.raydirx == 0)
// 			data->raycast.raydirx = 0.001;
// 		if (data->raycast.raydiry == 0)
// 			data->raycast.raydiry = 0.001;
		
		
// 		data->raycast.mapx = (int)data->player.px;
// 		data->raycast.mapy = (int)data->player.py;

// 		data->raycast.delta_dist_x = fabs(1 / data->raycast.raydirx);
// 		data->raycast.delta_dist_y = fabs(1 / data->raycast.raydiry);


// 		if (data->raycast.raydirx < 0)
// 		{
// 			data->raycast.stepx = -1;
// 			data->raycast.sidedistx = (data->player.px - data->raycast.mapx) * data->raycast.delta_dist_x;
// 		}
// 		else
// 		{
// 			data->raycast.stepx = 1;
// 			data->raycast.sidedistx = (data->raycast.mapx + 1.0 - data->player.px) * data->raycast.delta_dist_x;
// 		}

// 		if (data->raycast.raydiry < 0)
// 		{
// 			data->raycast.stepy = -1;
// 			data->raycast.side_dist_y = (data->player.py - data->raycast.mapy) * data->raycast.delta_dist_y;
// 		}
// 		else
// 		{
// 			data->raycast.stepy = 1;
// 			data->raycast.side_dist_y = (data->raycast.mapy + 1.0 - data->player.py) * data->raycast.delta_dist_y;
// 		}


// 		data->raycast.hit = 0;

// 		while (data->raycast.hit == 0)
// 		{
// 			if (data->raycast.sidedistx < data->raycast.side_dist_y)
// 			{
// 				data->raycast.sidedistx += data->raycast.delta_dist_x;
// 				data->raycast.mapx += data->raycast.stepx;
// 				data->raycast.side = 0;
// 			}
// 			else
// 			{
// 				data->raycast.side_dist_y += data->raycast.delta_dist_y;
// 				data->raycast.mapy += data->raycast.stepy;
// 				data->raycast.side = 1;
// 			}
// 			if (data->raycast.mapx >= 0 && data->raycast.mapy >= 0 && data->map_pars.map[data->raycast.mapy] && data->map_pars.map[data->raycast.mapy][data->raycast.mapx]
// 				&& data->map_pars.map[data->raycast.mapy][data->raycast.mapx] == '1')	
// 				data->raycast.hit = 1;

// 		}

// 		// draw_line(camerax, raydiry, data);

// 		if(data->raycast.side == 0)
// 			data->raycast.perpwall_dist = (data->raycast.sidedistx - data->raycast.delta_dist_x);
//     	else
// 			data->raycast.perpwall_dist = (data->raycast.side_dist_y - data->raycast.delta_dist_y);
			
// 		data->raycast.line_height = (int)(HEIGHT / data->raycast.perpwall_dist);
// 		data->raycast.draw_start = -data->raycast.line_height / 2 + HEIGHT / 2;
// 		if(data->raycast.draw_start < 0)
// 			data->raycast.draw_start = 0;

// 		data->raycast.draw_end = data->raycast.line_height / 2 + HEIGHT / 2;
// 		if(data->raycast.draw_end >= HEIGHT)
// 			data->raycast.draw_end = HEIGHT - 1;

			

// 		while(data->raycast.draw_start <= data->raycast.draw_end)
// 		{
// 			if (data->raycast.side == 0)
// 				my_mlx_pixel_put( &data->win, x, data->raycast.draw_start, 0xB82010);
// 			else
// 				my_mlx_pixel_put( &data->win, x, data->raycast.draw_start, 0x87180C);
// 			data->raycast.draw_start++;
// 		}
// 		x++;
// 	}
// 	draw_map(data);
// 	draw_square(data, (data->player.px * SIZE_SQUARE),(data->player.py * SIZE_SQUARE), NOIR, SIZE_SQUARE/ 3);
// 	mlx_put_image_to_window(data->win.mlx, data->win.win, data->win.img, 0, 0);
// }

int	get_window_pixel(t_win win, int x, int y)
{
	char	*dst;

	if (!win.addr)
		return (0);
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return (0);
	dst = win.addr + (y * win.line_length + x * (win.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int apply_shading(double distance, int color) // apply shading based on distance
{
    int r, g, b;
    double factor;
    int new_r, new_g, new_b;
    int new_color;

    if (distance < 1.0)
        distance = 1.0;

    factor = 1.0 / distance;
    if (factor < 0.1)
        factor = 0.1;

    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;

    new_r = (int)(r * factor);
    new_g = (int)(g * factor);
    new_b = (int)(b * factor);

    if (new_r > 255) new_r = 255;
    if (new_g > 255) new_g = 255;
    if (new_b > 255) new_b = 255;

    new_color = (new_r << 16) | (new_g << 8) | new_b;

    return new_color;
}


void drawRays2D(t_data *data)
{
	int x = 0;
	int y = 0;
	int color;
	int d;
	int texY;
	int texX;
	double wallX;
	t_img texture;
	
    while (x < WIDTH)
    {
        data->raycast.camerax = 2 * x / (double)WIDTH - 1; //calcul dir rayon chaque colonne
        data->raycast.raydirx = data->player.pdirx + data->player.planex * data->raycast.camerax;
        data->raycast.raydiry = data->player.pdiry + data->player.planey * data->raycast.camerax;

        if (data->raycast.raydirx == 0) data->raycast.raydirx = 0.001;
        if (data->raycast.raydiry == 0) data->raycast.raydiry = 0.001;

        data->raycast.mapx = (int)data->player.px; // convert pos joeurs coordonne case map
        data->raycast.mapy = (int)data->player.py;

        data->raycast.delta_dist_x = fabs(1 / data->raycast.raydirx); // distance rayon parcourus jusqua ligne map
        data->raycast.delta_dist_y = fabs(1 / data->raycast.raydiry);// fabs = valeur positivie 

        if (data->raycast.raydirx < 0)
        {
            data->raycast.stepx = -1;
            data->raycast.sidedistx = (data->player.px - data->raycast.mapx) * data->raycast.delta_dist_x;
        }
        else
        {
            data->raycast.stepx = 1;
            data->raycast.sidedistx = (data->raycast.mapx + 1.0 - data->player.px) * data->raycast.delta_dist_x;
        }

        if (data->raycast.raydiry < 0) // algo DDA pour avacer rayon de la map
        {
            data->raycast.stepy = -1;
            data->raycast.side_dist_y = (data->player.py - data->raycast.mapy) * data->raycast.delta_dist_y;
        }
        else
        {
            data->raycast.stepy = 1;
            data->raycast.side_dist_y = (data->raycast.mapy + 1.0 - data->player.py) * data->raycast.delta_dist_y;
        }

        data->raycast.hit = 0;
        while (data->raycast.hit == 0) //0 = vertical
        {
            if (data->raycast.sidedistx < data->raycast.side_dist_y) // si rayon a frapper un mur vertical ou horizontal
            {
                data->raycast.sidedistx += data->raycast.delta_dist_x;
                data->raycast.mapx += data->raycast.stepx;
                data->raycast.side = 0;
            }
            else
            {
                data->raycast.side_dist_y += data->raycast.delta_dist_y;
                data->raycast.mapy += data->raycast.stepy;
                data->raycast.side = 1;
            }

            if (data->map_pars.map[data->raycast.mapy] &&
                data->map_pars.map[data->raycast.mapy][data->raycast.mapx] == '1') // si mur stop DDA
                data->raycast.hit = 1;
        }
		// draw_line( data);

        if (data->raycast.side == 0)
            data->raycast.perpwall_dist = data->raycast.sidedistx - data->raycast.delta_dist_x;
        else
            data->raycast.perpwall_dist = data->raycast.side_dist_y - data->raycast.delta_dist_y; // fish eyes fix

        data->raycast.line_height = (int)(HEIGHT / data->raycast.perpwall_dist);
        data->raycast.draw_start = -data->raycast.line_height / 2 + HEIGHT / 2;
        if (data->raycast.draw_start < 0) data->raycast.draw_start = 0;
        data->raycast.draw_end = data->raycast.line_height / 2 + HEIGHT / 2;
        if (data->raycast.draw_end >= HEIGHT) data->raycast.draw_end = HEIGHT - 1; //  calcul hauteur de la colonne a dessiner a lecran 

        if (data->raycast.side == 0)
        {
            if (data->raycast.raydirx > 0)
                texture = data->texture.text_West;
            else
                texture = data->texture.text_East;
        }
        else
        {
            if (data->raycast.raydiry > 0)
                texture = data->texture.text_North;
            else
			
                texture = data->texture.text_South;
        }

        if (data->raycast.side == 0)
            wallX = data->player.py + data->raycast.perpwall_dist * data->raycast.raydiry;
        else
            wallX = data->player.px + data->raycast.perpwall_dist * data->raycast.raydirx;
        wallX -= floor(wallX);
    	texX = (int)(wallX * (double)texture.width);
        if ((data->raycast.side == 0 && data->raycast.raydirx > 0) ||
            (data->raycast.side == 1 && data->raycast.raydiry < 0))
            texX = texture.width - texX - 1;

		y = data->raycast.draw_start;
        while ( y <= data->raycast.draw_end)
        {
             d = y * 256 - HEIGHT * 128 + data->raycast.line_height * 128;
             texY = ((d * texture.height) / data->raycast.line_height) / 256;

            color = ((int *)texture.addr)[texture.height * texY + texX];
            color = apply_shading(data->raycast.perpwall_dist / 2, color);
            my_mlx_pixel_put(&data->win, x, y, color);
            if ((y + (data->raycast.draw_end - y) * 2) < HEIGHT)
            {
                int color_r = (color >> 16) & 0xFF;
                int color_g = (color >> 8) & 0xFF;
                int color_b = color & 0xFF;

                double opacity = 0.15;
                int floor_color = get_window_pixel(data->win, x, y + (data->raycast.draw_end - y) * 2);

                uint8_t floor_r = (floor_color >> 16) & 0xFF;
                uint8_t floor_g = (floor_color >> 8) & 0xFF;
                uint8_t floor_b = floor_color & 0xFF;

                int floor_r_d = (int)(floor_r * (1.0 - opacity) + color_r * opacity);
                int floor_g_d = (int)(floor_g * (1.0 - opacity) + color_g * opacity);
                int floor_b_d = (int)(floor_b * (1.0 - opacity) + color_b * opacity);
                
                int final_color = (floor_r_d << 16) | (floor_g_d << 8) | floor_b_d;
                my_mlx_pixel_put(&data->win, x, y + (data->raycast.draw_end - y) * 2, final_color);
            }
			y++;
        }
        x++;
    }
    draw_map(data);
    draw_square(data, (data->player.px * SIZE_SQUARE), (data->player.py * SIZE_SQUARE), NOIR, SIZE_SQUARE / 3);
    mlx_put_image_to_window(data->win.mlx, data->win.win, data->win.img, 0, 0);
}
