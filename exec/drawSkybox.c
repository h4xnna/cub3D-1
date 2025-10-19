/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawSkybox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:16:17 by pacda-si          #+#    #+#             */
/*   Updated: 2025/10/19 14:50:27 by pacda-si         ###   ########.fr       */
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

	int offset_x = (int)(skybox_width * (0.5 - atan2(data->player.pdirx, data->player.pdiry) / (2 * PI)));

	for (y = 0; y < HEIGHT / 2; y++)
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
		for (x = 0; x < WIDTH; x++)
		{		
			my_mlx_pixel_put(&data->win, x, y, data->floor);
		}
		y++;
	}
}
