/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 10:16:16 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/30 10:17:08 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	printf("F : ");
	if (info.floor)
		print_tab(info.floor);
	printf("\nC : ");
	if (info.ceiling)
		print_tab(info.ceiling);
	printf("\ncount : %d\n", info.count_info);
	print_char(map.map);
	printf("position map: %c\n", map.position);
	printf("start_x = %i\n", map.x_start);
	printf("start_y = %i\n", map.y_start);
}