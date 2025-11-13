/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:54:11 by hmimouni          #+#    #+#             */
/*   Updated: 2025/11/13 07:53:30 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void free_textures(t_data *data)
{
	if (data->texture->text_East->img)
		mlx_destroy_image(data->win->mlx, data->texture->text_East->img);
	if (data->texture->text_North->img)
		mlx_destroy_image(data->win->mlx, data->texture->text_North->img);
	if (data->texture->text_South->img)
		mlx_destroy_image(data->win->mlx,data->texture->text_South->img);
	if (data->texture->text_West->img)
		mlx_destroy_image(data->win->mlx, data->texture->text_West->img);
}

void	clean_exit(t_data *data)
{
	free_textures(data);
	free_win(data->win);
	free_info(data->map_info);
	free_tab(data->map_pars->map);
	exit(0);
}