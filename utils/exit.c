/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:19:57 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/29 18:29:14 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_splif(char **out, int i)
{
	while (i > 0)
	{
		free(out[i]);
		i--;
	}
	free(out);
}

void	free_textures(t_data *data)
{
	if (data->texture)
	{
		if (data->texture->text_east && data->texture->text_east->img)
			mlx_destroy_image(data->win->mlx, data->texture->text_east->img);
		if (data->texture->text_north && data->texture->text_north->img)
			mlx_destroy_image(data->win->mlx, data->texture->text_north->img);
		if (data->texture->text_south && data->texture->text_south->img)
			mlx_destroy_image(data->win->mlx, data->texture->text_south->img);
		if (data->texture->text_west && data->texture->text_west->img)
			mlx_destroy_image(data->win->mlx, data->texture->text_west->img);
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
		free_pars(data->info_pars);
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