/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 10:55:48 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/10 16:50:10 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_putstr_red(char *str)
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

t_img	*load_one_texture(t_data *data, t_img *tex, char *path)
{
	tex = malloc(sizeof(t_img));
	if (!tex)
	{
		error_message("Texture malloc failed");
		return (NULL);
	}
	tex->img = mlx_xpm_file_to_image(data->win->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		error_message("No such texture");
		ft_putstr_red(path);
		free(tex);
		return (NULL);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	return (tex);
}

static void	load_wall_textures(t_data *data)
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

void	load_textures(t_data *data)
{
	if (data->map_info->has_skybox)
	{
		data->texture->skybox = load_one_texture(data, data->texture->skybox,
				data->map_info->skybox);
		if (!data->texture->skybox)
			clean_exit(data);
	}
	else
		data->texture->skycolor = get_color_from_html(data->map_info->skybox);
	if (data->map_info->has_floor)
	{
		data->texture->floor = load_one_texture(data, data->texture->floor,
				data->map_info->floor);
		if (!data->texture->floor)
			clean_exit(data);
	}
	else
		data->texture->floor_color = get_color_from_html(data->map_info->floor);
	data->texture->exit = load_one_texture(data, data->texture->exit,
			data->map_info->exit);
	load_wall_textures(data);
	if (!data->texture->exit || !data->texture->text_south
		|| !data->texture->text_north || !data->texture->text_west
		|| !data->texture->text_east)
		clean_exit(data);
}
