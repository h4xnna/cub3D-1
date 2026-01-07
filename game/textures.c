/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 10:55:48 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/07 16:18:53 by pacda-si         ###   ########.fr       */
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

static t_img	*load_one_texture(t_data *data, t_img *tex, char *path)
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

static void	init_animation(t_animation *anim, int frame_count, double duration)
{
	anim->frame_count = frame_count;
	anim->current_frame = 0;
	anim->frame_time = duration / frame_count;
	anim->timer = 0.0;
	anim->duration = duration;
	anim->playing = 1;
}

static void	load_anim_textures(t_data *data, t_animation **anim, char *pattern,
		int frame_count)
{
	int		i;
	char	path[128];

	i = 0;
	while (i < frame_count)
	{
		snprintf(path, sizeof(path), pattern, i + 1);
		(*anim)->frames[i] = load_one_texture(data, (*anim)->frames[i], path);
		if (!(*anim)->frames[i])
		{
			while (--i >= 0)
				free_texture((*anim)->frames[i], data->win->mlx);
			free((*anim)->frames);
			free(*anim);
			clean_exit(data);
		}
		i++;
	}
}

static t_animation	*load_animation(t_data *data, char *pattern,
		int frame_count, double duration)
{
	t_animation	*anim;

	anim = malloc(sizeof(t_animation));
	if (!anim)
	{
		error_message("Animation malloc failed");
		clean_exit(data);
	}
	anim->frames = malloc(sizeof(t_img *) * frame_count);
	if (!anim->frames)
	{
		free(anim);
		clean_exit(data);
	}
	init_animation(anim, frame_count, duration);
	load_anim_textures(data, &anim, pattern, frame_count);
	return (anim);
}

unsigned int	get_color_from_html(char *color)
{
	unsigned int	value;
	char			c;
	int				i;

	value = 0;
	i = 1;
	while (i <= 6)
	{
		c = color[i];
		value <<= 4;
		if (c >= '0' && c <= '9')
			value |= (c - '0');
		else if (c >= 'A' && c <= 'F')
			value |= (c - 'A' + 10);
		else if (c >= 'a' && c <= 'f')
			value |= (c - 'a' + 10);
		else
			return (0);
		i++;
	}
	return (value);
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

void	load_animations(t_data *data)
{
	data->knife_anim = load_animation(data,
			"./assets/textures/anims/inspect/frame_%03d.xpm", 144, 4.78);
	data->deploy_anim = load_animation(data,
			"./assets/textures/anims/deploy/frame_%02d.xpm", 29, 0.96);
	data->lmb_anim = load_animation(data,
			"./assets/textures/anims/left/frame_%02d.xpm", 33, 1.09);
	data->rmb_anim = load_animation(data,
			"./assets/textures/anims/right/frame_%02d.xpm", 30, 1.0);
}
