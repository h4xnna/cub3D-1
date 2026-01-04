/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 08:00:02 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/04 13:56:31 by pacda-si         ###   ########.fr       */
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
	int				dst_x;
	t_color			rgb;
	int				x;
	int				y;

	y = -1;
	while (++y < src->height)
	{
		if (y + y_off < 0 || y + y_off >= HEIGHT)
			continue ;
		x = -1;
		while (++x < src->width)
		{
			dst_x = x + x_off;
			if (dst_x < 0 || dst_x >= WIDTH)
				continue ;
			color = *(unsigned int *)(src->addr + y * src->line_length + x
					* (src->bits_per_pixel / 8));
			make_color_from_int(color, &rgb);
			if (!(rgb.g > 100 && rgb.g > rgb.r * 1.5 && rgb.g > rgb.b * 1.5))
				my_mlx_pixel_put(win, dst_x, y + y_off, color);
		}
	}
}

static void	draw_skybox_pixel(t_data *data, int y, int offset_x)
{
	int	color;
	int	tex_x;
	int	tex_y;
	int	x;

	tex_y = (y * data->texture->skybox->height) / HEIGHT;
	x = 0;
	while (x < WIDTH)
	{
		tex_x = (offset_x + x) % data->texture->skybox->width;
		color = get_texture_pixel(data->texture->skybox, tex_x, tex_y);
		my_mlx_pixel_put(data->win, x, y, color);
		x++;
	}
}

void	draw_skybox(t_data *data)
{
	int		start_y;
	double	player_angle;
	int		offset_x;
	int		y;

	y = 0;
	start_y = HEIGHT / 2;
	player_angle = atan2(data->player->pdirx, data->player->pdiry);
	offset_x = (int)(data->texture->skybox->width * (0.5 - player_angle / (2
					* PI)));
	while (y < start_y)
	{
		draw_skybox_pixel(data, y, offset_x);
		y++;
	}
}
