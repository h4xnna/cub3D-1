/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 08:00:02 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/13 08:05:39 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	draw_animation(t_data *data, t_animation *anim, int x, int y)
{
	if (!anim->frames[anim->current_frame])
		return;
	mlx_put_image_to_window(data->win->mlx, data->win->win,
		anim->frames[anim->current_frame]->img, x, y);
}


void draw_image_to_buffer(t_win *win, t_img *src, int x_off, int y_off)
{
    int x, y;
    unsigned int color;

    for (y = 0; y < src->height; y++)
    {
        int dst_y = y + y_off;
        if (dst_y < 0 || dst_y >= HEIGHT)
            continue;

        for (x = 0; x < src->width; x++)
        {
            int dst_x = x + x_off;
            if (dst_x < 0 || dst_x >= WIDTH)
                continue;

            color = *(unsigned int *)(src->addr + y * src->line_length + x * (src->bits_per_pixel / 8));

            uint8_t r = (color >> 16) & 0xFF;
            uint8_t g = (color >> 8) & 0xFF;
            uint8_t b = color & 0xFF;

            if (!(g > 100 && g > r * 1.5 && g > b * 1.5))
                my_mlx_pixel_put(win, dst_x, dst_y, color);
        }
    }
}

void drawSkybox(t_data *data)
{
	int x, y, tex_x, tex_y;
	int start_y = HEIGHT / 2;

	double player_angle = atan2(data->player->pdirx, data->player->pdiry);
	int offset_x = (int)(data->texture->skybox->width *
						(0.5 - player_angle / (2 * PI)));
	for (y = 0; y < start_y; y++)
	{
		tex_y = (y * data->texture->skybox->height) / HEIGHT;
		for (x = 0; x < WIDTH; x++)
		{
			tex_x = (offset_x + x) % data->texture->skybox->width;
			int color = get_texture_pixel(data->texture->skybox, tex_x, tex_y);
			my_mlx_pixel_put(data->win, x, y, color);
		}
	}
}

static void draw_square(t_data *data, int x, int y, int color, int square_size)
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

void draw_map(t_data *data)
{
    int px = data->player->px;
    int py = data->player->py;

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
            if ((map_y >= 0 && map_y < data->map_pars->height) &&
                map_x >= 0 &&
                data->map_pars->map[map_y] &&
                data->map_pars->map[map_y][map_x])
                tile = data->map_pars->map[map_y][map_x];

            int color;
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
	if (data->map_pars->map[(int)(ray_y / SIZE_SQUARE)][(int)(ray_x / SIZE_SQUARE)]
			&& data->map_pars->map[(int)(ray_y / SIZE_SQUARE)][(int)(ray_x / SIZE_SQUARE)] == '1')
			return (1);
	return (0);
}
