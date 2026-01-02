/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 10:55:48 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/02 18:34:08 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putstr_Red(char *str)
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
	tex->img = mlx_xpm_file_to_image(data->win->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		error_message(" no texur");
		ft_putstr_Red(path);
		clean_exit(data);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	return (tex);
}

void	load_all_textures(t_data *data)
{
	data->texture->skybox = load_one_texture(data, data->texture->skybox,
			"./textures/4.xpm");
	data->texture->floor = load_one_texture(data, data->texture->floor,
			"./textures/metal.xpm");
	data->texture->exit = load_one_texture(data, data->texture->floor,
			"./textures/hole.xpm");
	data->texture->text_south = load_one_texture(data,
			data->texture->text_south, data->map_info->south);
	data->texture->text_north = load_one_texture(data,
			data->texture->text_north, data->map_info->north);
	data->texture->text_west = load_one_texture(data, data->texture->text_west,
			data->map_info->west);
	data->texture->text_east = load_one_texture(data, data->texture->text_east,
			data->map_info->east);
	data->knife_anim = load_animation(data,
			"./textures/inspect_frames/frame_%03d.xpm", 144, 4.78);
	data->deploy_anim = load_animation(data,
			"./textures/deploy_frames/frame_%02d.xpm", 29, 0.96);
	data->lmb_anim = load_animation(data,
			"./textures/lmb_frames/frame_%02d.xpm", 33, 1.09);
	data->rmb_anim = load_animation(data,
			"./textures/rmb_frames/frame_%02d.xpm", 30, 1.0);
}

t_animation	*load_animation(t_data *data, char *pattern, int frame_count,
		double duration)
{
	t_animation	*anim;
	char		path[128];

	anim = malloc(sizeof(t_animation));
	anim->frames = malloc(sizeof(t_img *) * frame_count);
	anim->frame_count = frame_count;
	anim->current_frame = 0;
	anim->duration = duration;
	anim->frame_time = duration / frame_count;
	anim->timer = 0;
	anim->playing = 0;
	for (int i = 0; i < frame_count; i++)
	{
		snprintf(path, sizeof(path), pattern, i + 1);
		anim->frames[i] = load_one_texture(data, anim->frames[i], path);
	}
	return (anim);
}
