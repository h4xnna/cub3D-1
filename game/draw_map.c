/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:21:09 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/02 19:25:26 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_square(t_data *data, int x, int y, int color, int square_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < square_size)
	{
		j = 0;
		while (j < square_size)
		{
			my_mlx_pixel_put(data->win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static unsigned int	switch_tile(char tile)
{
	if (tile == '1')
		return (0x707070);
	else if (tile == '0')
		return (BLANC);
	else if (tile == 'D')
		return (0x00FF00);
	else if (tile == 'L')
		return (0xC00000);
	return (0x000000);
}

static void	draw_case(t_data *data, int cases_x, int cases_y)
{
	int		map_y;
	int		map_x;
	int		draw_x;
	int		draw_y;
	char	tile;

	if ((cases_y == 0 && cases_x == 0) || (cases_y == 0
			&& cases_x == MINIMAP_RADIUS - 1) || (cases_y == MINIMAP_RADIUS - 1
			&& cases_x == 0) || (cases_y == MINIMAP_RADIUS - 1
			&& cases_x == MINIMAP_RADIUS - 1))
		return ;
	map_y = data->player->py + (cases_y - (MINIMAP_RADIUS / 2));
	map_x = data->player->px + (cases_x - (MINIMAP_RADIUS / 2));
	tile = 0;
	if ((map_y >= 0 && map_y < data->map_pars->height) && map_x >= 0
		&& data->map_pars->map[map_y] && data->map_pars->map[map_y][map_x])
		tile = data->map_pars->map[map_y][map_x];
	draw_x = cases_x * SIZE_SQUARE + SIZE_SQUARE;
	draw_y = cases_y * SIZE_SQUARE + SIZE_SQUARE;
	draw_square(data, draw_x, draw_y, switch_tile(tile), SIZE_SQUARE);
	cases_x++;
}

void	draw_map(t_data *data)
{
	int	player_x;
	int	player_y;
	int	cases_y;
	int	cases_x;

	cases_y = 0;
	while (cases_y < MINIMAP_RADIUS)
	{
		cases_x = 0;
		while (cases_x < MINIMAP_RADIUS)
		{
			draw_case(data, cases_x, cases_y);
			cases_x++;
		}
		cases_y++;
	}
	player_x = (MINIMAP_RADIUS / 2) * SIZE_SQUARE + SIZE_SQUARE / 4
		+ SIZE_SQUARE;
	player_y = (MINIMAP_RADIUS / 2) * SIZE_SQUARE + SIZE_SQUARE / 4
		+ SIZE_SQUARE;
	draw_square(data, player_x, player_y, ROUGE, SIZE_SQUARE / 2);
}
