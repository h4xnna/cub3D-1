/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:16:44 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/06 11:33:42 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_doors(t_door *doors)
{
	int	i;

	i = 1;
	while (doors)
	{
		printf("Door [%d], x : %d, y : %d\n", i, doors->x, doors->y);
		doors = doors->next;
		i++;
	}
}

void	doors_add_back(t_door **doors, t_door *new)
{
	t_door	*head;

	if (!new)
		return ;
	if (!*doors)
	{
		*doors = new;
		return ;
	}
	head = *doors;
	while (head->next)
		head = head->next;
	head->next = new;
}

t_door	*new_door(int x, int y)
{
	t_door	*new;

	new = ft_calloc(1, sizeof(t_door));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	return (new);
}

void	make_doors(t_data *data)
{
	char	**map;
	int		i;
	int		j;
	t_door	*door;

	map = data->map_pars->map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'D')
			{
				door = new_door(j, i);
				if (!door)
				{
					error_message("Malloc failed for door");
					clean_exit(data);
				}
				doors_add_back(&data->doors, door);
			}
		}
	}
}
