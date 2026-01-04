/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:06:04 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/04 13:49:12 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_door	*find_door(t_door *doors, int y, int x)
{
	while (doors)
	{
		if (doors->y == y && doors->x == x)
			return (doors);
		doors = doors->next;
	}
	return (NULL);
}

static void	update_single_door(t_data *data, t_door *door)
{
	if (sqrt(pow(data->player->px - (door->x + 0.5), 2) + pow(data->player->py
				- (door->y + 0.5), 2)) < 1.45)
	{
		if (door->opening >= 0.0 || !door->opened)
			door->opened = 1;
	}
	else if (door->opening >= 0.0)
	{
		data->map_pars->map[door->y][door->x] = 'D';
		door->opened = -1;
	}
	if ((door->opening >= 0.0 && door->opening <= 1.0))
		door->opening += data->player->delta_time * (door->opened * 0.8);
	if (door->opening >= 1.0)
	{
		door->opening = 1.0;
		data->map_pars->map[door->y][door->x] = '0';
	}
	if (door->opening <= 0.0)
		door->opening = 0.0;
}

void	update_doors(t_data *data)
{
	t_door	*door;

	door = data->doors;
	while (door)
	{
		update_single_door(data, door);
		door = door->next;
	}
}
