#include "../cub3d.h"


int	get_texture_pixel(t_img *img, int x, int y)
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
	int x, y;
	int tex_x, tex_y;
	int start_y = HEIGHT / 2;

	int offset_x = (int)(data->texture->skybox->width * (0.5 - atan2(data->player->pdirx, data->player->pdiry) / (2 * PI)));

	for (y = 0; y < start_y; y++)
	{
		tex_y = (y * data->texture->skybox->height) / HEIGHT;

		for (x = 0; x < WIDTH; x++)
		{
			tex_x = (offset_x + x) % data->texture->skybox->width;
			my_mlx_pixel_put(data->win, x, y, get_texture_pixel(data->texture->skybox, tex_x, tex_y));
		}
	}

	// while (y < HEIGHT)
	// {
	// 	tex_y = (y * skybox_height) / HEIGHT;

	// 	for (x = 0; x < WIDTH; x++)
	// 	{
	// 		tex_x = (offset_x + x) % skybox_width;
	// 		int tex_color = get_texture_pixel(&data->texture->skybox, tex_x, tex_y);
	// 		my_mlx_pixel_put(&data->win, x, y, tex_color);
	// 	}
	// 	y++;
	// }
}
