/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 10:16:16 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/10 16:13:22 by pacda-si         ###   ########.fr       */
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

void	print_char(char **str)
{
	int	j;

	j = 0;
	if (!str)
		return ;
	while (str[j])
	{
		printf("%s\n", str[j]);
		j++;
	}
}

int	print_tab(int *tab)
{
	int	i;

	i = 0;
	if (!tab)
	{
		error_message(" info");
		return (1);
	}
	while (i < 3)
	{
		printf("%i, ", tab[i]);
		i++;
	}
	return (0);
}

void	print_info(t_map_info info, t_map_pars map)
{
	printf("NORD : %s\n", info.north);
	printf("SUD : %s\n", info.south);
	printf("WEST : %s\n", info.west);
	printf("EAST : %s\n", info.east);
	printf("\ncount : %d\n", info.count_info);
	print_char(map.map);
	printf("position map: %c\n", map.position);
	printf("start_x = %i\n", map.x_start);
	printf("start_y = %i\n", map.y_start);
}
