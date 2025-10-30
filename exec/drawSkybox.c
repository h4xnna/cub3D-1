#include "../cub3d.h"

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
