/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 08:00:02 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/13 11:52:41 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_animation(t_data *data, t_animation *anim, int x, int y)
{
	if (!anim->frames[anim->current_frame])
		return ;
	mlx_put_image_to_window(data->win->mlx, data->win->win,
		anim->frames[anim->current_frame]->img, x, y);
}

void	draw_image_to_buffer(t_win *win, t_img *src, int x_off, int y_off)
{
	unsigned int	color;
	int				dst_y;
	int				dst_x;
	t_color         rgb;
	int x;
    int y;
    y = 0;
    x = 0;
	while (y < src->height)
	{
		dst_y = y + y_off;
		if (dst_y < 0 || dst_y >= HEIGHT)
			continue ;
		while (x < src->width)
		{
			dst_x = x + x_off;
			if (dst_x < 0 || dst_x >= WIDTH)
				continue ;
			color = *(unsigned int *)(src->addr + y * src->line_length + x
					* (src->bits_per_pixel / 8));
			rgb.r = (color >> 16) & 0xFF;
			rgb.g = (color >> 8) & 0xFF;
			rgb.b = color & 0xFF;
			if (!(rgb.g > 100 && rgb.g > rgb.r * 1.5 && rgb.g > rgb.b * 1.5))
				my_mlx_pixel_put(win, dst_x, dst_y, color);
            x++;
		}
        y++;
	}
}

void	drawskybox(t_data *data)
{
	int		start_y;
	double	player_angle;
	int		offset_x;
	int		color;

	int x;
    int y;
    int tex_x;
    int tex_y;
    y = 0;
	start_y = HEIGHT / 2;
	player_angle = atan2(data->player->pdirx, data->player->pdiry);
	offset_x = (int)(data->texture->skybox->width * (0.5 - player_angle / (2
					* PI)));
	while ( y < start_y)
	{
		tex_y = (y * data->texture->skybox->height) / HEIGHT;
		for (x = 0; x < WIDTH; x++)
		{
			tex_x = (offset_x + x) % data->texture->skybox->width;
			color = get_texture_pixel(data->texture->skybox, tex_x, tex_y);
			my_mlx_pixel_put(data->win, x, y, color);
		}
        y++;
	}
}

static void	draw_square(t_data *data, int x, int y, int color, int square_size)
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
			my_mlx_pixel_put(data->win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	int		px;
	int		py;
	int		map_y;
	int		map_x;
	char	tile;
	int		color;
	int		draw_x;
	int		draw_y;
	int		player_x;
	int		player_y;

	px = data->player->px;
	py = data->player->py;
	for (int yCases = 0; yCases < MINIMAP_RADIUS; yCases++)
	{
		for (int xCases = 0; xCases < MINIMAP_RADIUS; xCases++)
		{
			if ((yCases == 0 && xCases == 0) || (yCases == 0
					&& xCases == MINIMAP_RADIUS - 1)
				|| (yCases == MINIMAP_RADIUS - 1 && xCases == 0)
				|| (yCases == MINIMAP_RADIUS - 1 && xCases == MINIMAP_RADIUS
					- 1))
				continue ;
			map_y = py + (yCases - (MINIMAP_RADIUS / 2));
			map_x = px + (xCases - (MINIMAP_RADIUS / 2));
			tile = 0;
			if ((map_y >= 0 && map_y < data->map_pars->height) && map_x >= 0
				&& data->map_pars->map[map_y]
				&& data->map_pars->map[map_y][map_x])
				tile = data->map_pars->map[map_y][map_x];
			if (tile == '1')
				color = 0x707070;
			else if (tile == '0')
				color = BLANC;
			else if (tile == 'D')
				color = 0x00FF00;
			else if (tile == 'L')
				color = 0xC00000;
			else
				color = 0x000000;
			draw_x = xCases * SIZE_SQUARE + SIZE_SQUARE;
			draw_y = yCases * SIZE_SQUARE + SIZE_SQUARE;
			draw_square(data, draw_x, draw_y, color, SIZE_SQUARE);
		}
	}
	player_x = (MINIMAP_RADIUS / 2) * SIZE_SQUARE + SIZE_SQUARE / 4
		+ SIZE_SQUARE;
	player_y = (MINIMAP_RADIUS / 2) * SIZE_SQUARE + SIZE_SQUARE / 4
		+ SIZE_SQUARE;
	draw_square(data, player_x, player_y, ROUGE, SIZE_SQUARE / 2);
}

int	is_wall(t_data *data, float ray_x, float ray_y)
{
	if (data->map_pars->map[(int)(ray_y / SIZE_SQUARE)][(int)(ray_x
			/ SIZE_SQUARE)] && data->map_pars->map[(int)(ray_y
			/ SIZE_SQUARE)][(int)(ray_x / SIZE_SQUARE)] == '1')
		return (1);
	return (0);
}
