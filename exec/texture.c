/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 10:55:48 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/25 15:14:17 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void load_one_texture(t_data *data, t_img *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(data->win.mlx, path, &tex->width, &tex->height);
    if (!tex->img)
    {
        printf("Error : no textur %s\n", path);
        exit(1);
    }
    tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel, &tex->line_length, &tex->endian);
}


void load_all_textures(t_data *data)
{
    load_one_texture(data, &data->texture.text_South, data->map_info.south);
    load_one_texture(data, &data->texture.text_North, data->map_info.north);
    load_one_texture(data, &data->texture.text_West, data->map_info.west);
    load_one_texture(data, &data->texture.text_East, data->map_info.east);
}
