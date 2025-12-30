/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 10:55:48 by hmimouni          #+#    #+#             */
/*   Updated: 2025/12/30 10:03:53 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putstr_red(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, RED, sizeof(RED) - 1);
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
	write(2, RESET, sizeof(RESET) - 1);
}

static t_img	*load_one_texture(t_data *data, t_img *tex, char *path)
{
	tex = malloc(sizeof(t_img));
	if (!tex)
	{
		error_message("Memory allocation failed for texture");
		clean_exit(data);
	}
	tex->img = mlx_xpm_file_to_image(data->win->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		free(tex);
		error_message("No such texture file: ");
		ft_putstr_red(path);
		clean_exit(data);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	return (tex);
}

void	load_all_textures(t_data *data)
{
	data->texture->text_south = load_one_texture(data,
			data->texture->text_south, data->map_info->south);
	data->texture->text_north = load_one_texture(data,
			data->texture->text_north, data->map_info->north);
	data->texture->text_west = load_one_texture(data, data->texture->text_west,
			data->map_info->west);
	data->texture->text_east = load_one_texture(data, data->texture->text_east,
			data->map_info->east);
}
