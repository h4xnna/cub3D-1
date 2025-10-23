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
	int floor_r = (data->floor >> 16) & 0xFF;
	int floor_g = (data->floor >> 8) & 0xFF;
	int floor_b = data->floor & 0xFF;

while (y < HEIGHT)
{
	tex_y = (y * skybox_height) / HEIGHT;

    double dark_factor = 0.0;
    if (y >= HEIGHT / 2)
        dark_factor = (double)(HEIGHT - y) / (HEIGHT / 2);
    if (dark_factor > 1.0) dark_factor = 1.0;

    // Darkened floor color
    int floor_r_d = (int)(floor_r * (1.0 - dark_factor));
    int floor_g_d = (int)(floor_g * (1.0 - dark_factor));
    int floor_b_d = (int)(floor_b * (1.0 - dark_factor));

    for (x = 0; x < WIDTH; x++)
    {
        // Get texture color at this pixel

		tex_x = (offset_x + x) % skybox_width;

        int tex_color = get_texture_pixel(&data->skybox, tex_x, tex_y); // implement this
        int tex_r = (tex_color >> 16) & 0xFF;
        int tex_g = (tex_color >> 8) & 0xFF;
        int tex_b = tex_color & 0xFF;

        // Texture opacity (0.0 = fully transparent, 1.0 = fully opaque)
        double tex_opacity = 0.2; // 30% texture

        // Blend texture over floor
        int final_r = (int)(floor_r_d * (1.0 - tex_opacity) + tex_r * tex_opacity);
        int final_g = (int)(floor_g_d * (1.0 - tex_opacity) + tex_g * tex_opacity);
        int final_b = (int)(floor_b_d * (1.0 - tex_opacity) + tex_b * tex_opacity);

        int final_color = (final_r << 16) | (final_g << 8) | final_b;

        my_mlx_pixel_put(&data->win, x, y, final_color);
    }

    y++;
}
}
