/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:54:11 by hmimouni          #+#    #+#             */
/*   Updated: 2025/12/13 10:33:24 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void free_textures(t_data *data)
{
	if (data->texture->text_east->img)
		mlx_destroy_image(data->win->mlx, data->texture->text_east->img);
	if (data->texture->text_north->img)
		mlx_destroy_image(data->win->mlx, data->texture->text_north->img);
	if (data->texture->text_south->img)
		mlx_destroy_image(data->win->mlx,data->texture->text_south->img);
	if (data->texture->text_west->img)
		mlx_destroy_image(data->win->mlx, data->texture->text_west->img);
}

void	clean_exit(t_data *data)
{
	free_textures(data);
	free_win(data->win);
	free_info(data->map_info);
	free_tab(data->map_pars->map);
	exit(0);
}