/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:09:43 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/29 18:10:37 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_perp_wall_dist(t_data *data)
{
	if (data->raycast->side == 0)
		data->raycast->perpwall_dist = data->raycast->sidedistx
			- data->raycast->delta_dist_x;
	else
		data->raycast->perpwall_dist = data->raycast->side_dist_y
			- data->raycast->delta_dist_y; // fish eyes fix
}

void	calculate_line(t_data *data)
{
	data->raycast->line_height = (int)(HEIGHT / data->raycast->perpwall_dist);
	data->raycast->draw_start = -data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_start < 0)
		data->raycast->draw_start = 0;
	data->raycast->draw_end = data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_end >= HEIGHT)
		data->raycast->draw_end = HEIGHT - 1;
	//  calcul hauteur de la colonne a dessiner a lecran
}

void	get_wall_texture(t_data *data, t_img **texture)
{
	if (data->raycast->side == 0)
	{
		if (data->raycast->raydirx > 0)
			*texture = data->texture->text_west;
		else
			*texture = data->texture->text_east;
	}
	else
	{
		if (data->raycast->raydiry > 0)
			*texture = data->texture->text_north;
		else
			*texture = data->texture->text_south;
	}
}

void	get_texture_x(t_data *data, t_img *texture, int *tex_x)
{
	double	wall_x;

	if (data->raycast->side == 0)
		wall_x = data->player->py + data->raycast->perpwall_dist
			* data->raycast->raydiry;
	else
		wall_x = data->player->px + data->raycast->perpwall_dist
			* data->raycast->raydirx;
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * (double)texture->width);
	if ((data->raycast->side == 0 && data->raycast->raydirx > 0)
		|| (data->raycast->side == 1 && data->raycast->raydiry < 0))
		*tex_x = texture->width - *tex_x - 1;
}

void	draw_line(t_data *data, t_img *texture, int tex_x, int x)
{
	int	y;
	int	color;
	int	d;
	int	tex_y;

	y = -1;
	while (++y < data->raycast->draw_start)
		my_mlx_pixel_put(data->win, x, y, data->raycast->ceiling);
	while (y <= data->raycast->draw_end)
	{
		d = y * 256 - HEIGHT * 128 + data->raycast->line_height * 128;
		tex_y = ((d * texture->height) / data->raycast->line_height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		color = ((int *)texture->addr)[texture->height * tex_y + tex_x];
		my_mlx_pixel_put(data->win, x, y, color);
		y++;
	}
	while (y < HEIGHT - 1)
	{
		my_mlx_pixel_put(data->win, x, y, data->raycast->floor);
		y++;
	}
}