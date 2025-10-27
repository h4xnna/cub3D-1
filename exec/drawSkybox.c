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
	int skybox_width = data->texture.skybox.width;
	int skybox_height = data->texture.skybox.height;
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
			my_mlx_pixel_put(&data->win, x, y, get_texture_pixel(&data->texture.skybox, tex_x, tex_y));
		}
	}

	while (y < HEIGHT)
	{
		tex_y = (y * skybox_height) / HEIGHT;

		double dark_factor = 0.0;
		if (y >= HEIGHT / 2)
			dark_factor = (double)(HEIGHT - y) / (HEIGHT / 2);
		if (dark_factor > 1.0) dark_factor = 1.0;

		int floor_r_d = (int)(data->map_info.floor[0] * (1.0 - dark_factor));
		int floor_g_d = (int)(data->map_info.floor[1] * (1.0 - dark_factor));
		int floor_b_d = (int)(data->map_info.floor[2] * (1.0 - dark_factor));

		for (x = 0; x < WIDTH; x++)
		{

			tex_x = (offset_x + x) % skybox_width;

			int tex_color = get_texture_pixel(&data->texture.skybox, tex_x, tex_y); // implement this
			int tex_r = (tex_color >> 16) & 0xFF;
			int tex_g = (tex_color >> 8) & 0xFF;
			int tex_b = tex_color & 0xFF;

			double tex_opacity = 0.3;

			int final_r = (int)(floor_r_d * (1.0 - tex_opacity) + tex_r * tex_opacity);
			int final_g = (int)(floor_g_d * (1.0 - tex_opacity) + tex_g * tex_opacity);
			int final_b = (int)(floor_b_d * (1.0 - tex_opacity) + tex_b * tex_opacity);

			int final_color = (final_r << 16) | (final_g << 8) | final_b;

			my_mlx_pixel_put(&data->win, x, y, final_color);
		}

		y++;
	}
}
