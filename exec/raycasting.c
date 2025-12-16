/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:51:22 by hmimouni          #+#    #+#             */
/*   Updated: 2025/12/16 17:09:22 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_window_pixel(t_win *win, int x, int y)
{
	char	*dst;

	if (!win->addr)
		return (0);
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return (0);
	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	initStepSideDist(t_data *data)
{
	if (data->raycast->raydirx < 0)
	{
		data->raycast->stepx = -1;
		data->raycast->sidedistx = (data->player->px - data->raycast->mapx)
			* data->raycast->delta_dist_x;
	}
	else
	{
		data->raycast->stepx = 1;
		data->raycast->sidedistx = (data->raycast->mapx + 1.0
				- data->player->px) * data->raycast->delta_dist_x;
	}
	if (data->raycast->raydiry < 0) // algo DDA pour avacer rayon de la map
	{
		data->raycast->stepy = -1;
		data->raycast->side_dist_y = (data->player->py - data->raycast->mapy)
			* data->raycast->delta_dist_y;
	}
	else
	{
		data->raycast->stepy = 1;
		data->raycast->side_dist_y = (data->raycast->mapy + 1.0
				- data->player->py) * data->raycast->delta_dist_y;
	}
}

void	initRaycasting(t_data *data, int x)
{
	data->raycast->camerax = 2 * x / (double)WIDTH - 1;
	// calcul dir rayon chaque colonne
	data->raycast->raydirx = data->player->pdirx + data->player->planex
		* data->raycast->camerax;
	data->raycast->raydiry = data->player->pdiry + data->player->planey
		* data->raycast->camerax;
	if (data->raycast->raydirx == 0)
		data->raycast->raydirx = 0.001;
	if (data->raycast->raydiry == 0)
		data->raycast->raydiry = 0.001;
	data->raycast->mapx = (int)data->player->px;
	// convert pos joeurs coordonne case map
	data->raycast->mapy = (int)data->player->py;
	data->raycast->delta_dist_x = fabs(1 / data->raycast->raydirx);
	// distance rayon parcourus jusqua ligne map
	data->raycast->delta_dist_y = fabs(1 / data->raycast->raydiry);
	// fabs = valeur positivie
	initStepSideDist(data);
}

void	performDDA(t_data *data)
{
	data->raycast->hit = 0;
	while (data->raycast->hit == 0) // 0 = vertical
	{
		if (data->raycast->sidedistx < data->raycast->side_dist_y)
		// si rayon a frapper un mur vertical ou horizontal
		{
			data->raycast->sidedistx += data->raycast->delta_dist_x;
			data->raycast->mapx += data->raycast->stepx;
			data->raycast->side = 0;
		}
		else
		{
			data->raycast->side_dist_y += data->raycast->delta_dist_y;
			data->raycast->mapy += data->raycast->stepy;
			data->raycast->side = 1;
		}
		if (data->map_pars->map[data->raycast->mapy]
			&& (data->map_pars->map[data->raycast->mapy][data->raycast->mapx] == '1'))
			// si mur stop DDA
			data->raycast->hit = 1;
	}
}

void	getPerpWallDist(t_data *data)
{
	if (data->raycast->side == 0)
		data->raycast->perpwall_dist = data->raycast->sidedistx
			- data->raycast->delta_dist_x;
	else
		data->raycast->perpwall_dist = data->raycast->side_dist_y
			- data->raycast->delta_dist_y; // fish eyes fix
}
void	calculateLine(t_data *data)
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

void	getWallTexture(t_data *data, t_img **texture)
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

void	getTextureX(t_data *data, t_img *texture, int *texX)
{
	double	wallX;

	if (data->raycast->side == 0)
		wallX = data->player->py + data->raycast->perpwall_dist
			* data->raycast->raydiry;
	else
		wallX = data->player->px + data->raycast->perpwall_dist
			* data->raycast->raydirx;
	wallX -= floor(wallX);
	*texX = (int)(wallX * (double)texture->width);
	if ((data->raycast->side == 0 && data->raycast->raydirx > 0)
		|| (data->raycast->side == 1 && data->raycast->raydiry < 0))
		*texX = texture->width - *texX - 1;
}

void	drawLine(t_data *data, t_img *texture, int texX, int x)
{
	int	y;
	int	color;
	int	d;
	int	texY;

	y = -1;
	while (++y < data->raycast->draw_start)
		my_mlx_pixel_put(data->win, x, y, data->raycast->ceiling);
	while (y <= data->raycast->draw_end)
	{
		d = y * 256 - HEIGHT * 128 + data->raycast->line_height * 128;
		texY = ((d * texture->height) / data->raycast->line_height) / 256;
		if (texY < 0)
			texY = 0;
		color = ((int *)texture->addr)[texture->height * texY + texX];
		my_mlx_pixel_put(data->win, x, y, color);
		y++;
	}
	while (y < HEIGHT - 1)
	{
		my_mlx_pixel_put(data->win, x, y, data->raycast->floor);
		y++;
	}
}

void	drawRays2D(t_data *data)
{
	int		x;
	int		texX;
	t_img	*texture;

	x = 0;
	while (x < WIDTH)
	{
		initRaycasting(data, x);
		performDDA(data);
		getPerpWallDist(data);
		calculateLine(data);
		getWallTexture(data, &texture);
		getTextureX(data, texture, &texX);
		drawLine(data, texture, texX, x);
		x++;
	}
	mlx_put_image_to_window(data->win->mlx, data->win->win, data->win->img, 0,
		0);
}
