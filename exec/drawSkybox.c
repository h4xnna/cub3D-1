/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawSkybox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:16:17 by pacda-si          #+#    #+#             */
/*   Updated: 2025/10/21 21:10:49 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_texture_pixel(t_texture *img, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0);
	dst = img->addr
		+ (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void drawSkybox(t_data *data)
{
	int skybox_width = data->skybox.width;
	int skybox_height = data->skybox.height;
	int x, y;
	int tex_x, tex_y;
	int start_y = HEIGHT / 2;

	int offset_x = (int)(skybox_width * (0.5 - atan2(data->player.pdirx, data->player.pdiry) / (2 * PI)));

	for (y = 0; y < start_y; y++)
	{
		tex_y = (y * skybox_height) / HEIGHT;

		for (x = 0; x < WIDTH; x++)
		{
			tex_x = (offset_x + x) % skybox_width;
			my_mlx_pixel_put(&data->win, x, y, get_texture_pixel(&data->skybox, tex_x, tex_y));
		}
	}
	while (y < HEIGHT)
	{
		double factor = (double)(y - start_y) / (HEIGHT - start_y);
		if (factor > 1.0) factor = 1.0;
		if (factor < 0.0) factor = 0.0;
	
		int r = (data->floor >> 16) & 0xFF;
		int g = (data->floor >> 8) & 0xFF;
		int b = data->floor & 0xFF;

		int shaded_r = (int)(r * factor);
		int shaded_g = (int)(g * factor);
		int shaded_b = (int)(b * factor);

		int shaded_color = (shaded_r << 16) | (shaded_g << 8) | shaded_b;

		for (x = 0; x < WIDTH; x++)
		{		
			my_mlx_pixel_put(&data->win, x, y, shaded_color);
		}
		y++;
	}
}
