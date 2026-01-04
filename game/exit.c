/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:54:11 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/04 13:34:50 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_texture(t_img *texture, void *mlx)
{
	if (texture)
	{
		if (texture->img)
			mlx_destroy_image(mlx, texture->img);
		free(texture);
	}
}

void	free_textures(t_data *data)
{
	if (data->texture)
	{
		if (data->texture->text_east)
			free_texture(data->texture->text_east, data->win->mlx);
		if (data->texture->text_north)
			free_texture(data->texture->text_north, data->win->mlx);
		if (data->texture->text_south)
			free_texture(data->texture->text_south, data->win->mlx);
		if (data->texture->text_west)
			free_texture(data->texture->text_west, data->win->mlx);
		free(data->texture);
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->map_pars)
	{
		free_tab(data->map_pars->map);
		free(data->map_pars);
	}
	if (data->map_info)
		free_info(data->map_info);
	if (data->info_pars)
	{
		free_pars(data->info_pars);
		free(data->info_pars);
	}
	if (data->player)
		free(data->player);
	if (data->raycast)
		free(data->raycast);
	if (data->texture)
		free_textures(data);
	if (data->win)
		free_win(data->win);
	if (data->fd >= 0)
		close(data->fd);
	free(data);
}

void	clean_exit(t_data *data)
{
	free_data(data);
	exit(0);
}
