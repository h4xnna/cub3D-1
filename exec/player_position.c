/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:51:35 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/25 10:14:42 by hmimouni         ###   ########.fr       */
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
			my_mlx_pixel_put(&data->win, x, y, colors_ceiling);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&data->win, x, y, colors_floor);
			x++;
		}
		y++;
	}
    mlx_put_image_to_window(data->win.mlx, data->win.win, data->win.img, 0, 0);

}

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	if (!win || !win->addr)
		return ; 

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ; 

	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
void    clear_window(t_win *win)
{
    ft_bzero(win->addr, WIDTH * HEIGHT * (win->bits_per_pixel / 8));
}

