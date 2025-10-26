/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 10:55:48 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/26 15:24:01 by hmimouni         ###   ########.fr       */
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
static void	load_one_texture(t_data *data, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(data->win.mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		error_message(" no textur");
        ft_putstr_Red(path);
        clean_exit(data);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
}

void	load_all_textures(t_data *data)
{
    load_one_texture(data, &data->texture.skybox, "./texture/3.xpm");
	load_one_texture(data, &data->texture.text_South, data->map_info.south);
	load_one_texture(data, &data->texture.text_North, data->map_info.north);
	load_one_texture(data, &data->texture.text_West, data->map_info.west);
	load_one_texture(data, &data->texture.text_East, data->map_info.east);
}

