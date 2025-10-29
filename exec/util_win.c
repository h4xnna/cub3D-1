/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_win->c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:30:00 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/26 16:29:48 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	split_win(t_data *data)
{
	int	x;
	int	y;
	int	colors_ceiling;
	int	colors_floor;

	colors_ceiling = rgb_to_hex_int(data, data->map_info->ceiling);
	colors_floor = rgb_to_hex_int(data, data->map_info->floor);
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(data->win, x, y, colors_ceiling);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(data->win, x, y, colors_floor);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->win->mlx, data->win->win, data->win->img, 0, 0);
}

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	if (!win || !win->addr)
		return ;
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
void	clear_window(t_win *win)
{
	ft_bzero(win->addr, WIDTH * HEIGHT * (win->bits_per_pixel / 8));
}
t_win    *init_win(void)
{
    t_win    *win;

    win = (t_win *)ft_calloc(1, sizeof(t_win));
    if (!win)
        return (NULL);
    win->mlx = NULL;
    win->win = NULL;
    win->img = NULL;
    win->addr = NULL;
    win->bits_per_pixel = 0;
    win->line_length = 0;
    win->endian = 0;
    win->mlx = mlx_init();
    if (!win->mlx)
        return (NULL);
    win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT, "damn");
    if (!win->win)
        return (NULL);
    win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
    if (!win->img)
        return (NULL);
    win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
            &win->line_length, &win->endian);
    mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
    return (win);
}
void	free_win(t_win *win)
{
	if (win->img)
		mlx_destroy_image(win->mlx, win->img);
	if (win->win)
		mlx_destroy_window(win->mlx, win->win);
	if (win->mlx)
	{
		mlx_destroy_display(win->mlx);
		free(win->mlx);
	}
}