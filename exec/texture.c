/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 10:55:48 by hmimouni          #+#    #+#             */
/*   Updated: 2025/11/12 15:25:03 by pacda-si         ###   ########.fr       */
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

static t_img    *load_one_texture(t_data *data, t_img *tex, char *path)
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
    data->texture->skybox = load_one_texture(data, data->texture->skybox, "./texture/7.xpm");
    data->texture->floor = load_one_texture(data, data->texture->floor, "./texture/metal.xpm");
    data->texture->exit = load_one_texture(data, data->texture->floor, "./texture/hole.xpm");
	data->texture->text_South = load_one_texture(data, data->texture->text_South, data->map_info->south);
	data->texture->text_North = load_one_texture(data, data->texture->text_North, data->map_info->north);
	data->texture->text_West = load_one_texture(data, data->texture->text_West, data->map_info->west);
	data->texture->text_East = load_one_texture(data, data->texture->text_East, data->map_info->east);
	data->knife_anim = load_animation(data, "inspect_frames/frame_%03d.xpm", 287);
}


t_animation	*load_animation(t_data *data, char *pattern, int frame_count)
{
	t_animation	*anim = malloc(sizeof(t_animation));
	anim->frames = malloc(sizeof(t_img *) * frame_count);
	anim->frame_count = frame_count;
	anim->current_frame = 0;
	anim->frame_time = 1.0 / 60.0;
	anim->timer = 0;
	anim->playing = 0;

	char path[128];
	for (int i = 0; i < frame_count; i++)
	{
		snprintf(path, sizeof(path), pattern, i + 1);
		anim->frames[i] = load_one_texture(data, anim->frames[i], path);
	}
	return (anim);
}
