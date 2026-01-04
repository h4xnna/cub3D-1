/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:48:10 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/04 21:46:40 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_window(t_win *win)
{
	ft_bzero(win->addr, WIDTH * HEIGHT * (win->bits_per_pixel / 8));
}

t_win	*init_win(void)
{
	t_win	*win;

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
	free(win);
}
