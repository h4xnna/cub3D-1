/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:53:12 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/10 19:22:45 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	flood_fill_helper(char **map, int x, int y)
{
	if (y < 0 || !map[y] || x < 0 || map[y][x] == '\0')
		return (0);
	if (map[y][x] == ' ')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (1);
	if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
		|| map[y][x] == 'W')
	{
		map[y][x] = '0';
	}
	map[y][x] = 'X';
	if (!flood_fill_helper(map, x + 1, y))
		return (0);
	if (!flood_fill_helper(map, x - 1, y))
		return (0);
	if (!flood_fill_helper(map, x, y + 1))
		return (0);
	if (!flood_fill_helper(map, x, y - 1))
		return (0);
	return (1);
}

static char	**clone_map(char **map)
{
	char	**new_map;
	int		i;
	int		map_len;

	i = 0;
	if (!map || !*map)
		return (NULL);
	map_len = len_tab(map);
	new_map = malloc(sizeof(char *) * (map_len + 1));
	if (!new_map)
		return (NULL);
	while (map[i])
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
			return (free_splif(new_map, i), NULL);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

int	flood_fill(t_map_pars *map)
{
	int		x;
	int		y;
	int		error;
	char	**test_map;

	x = map->x_start;
	y = map->y_start;
	error = 0;
	test_map = clone_map(map->map);
	if (!flood_fill_helper(test_map, x, y))
		error = 1;
	free_tab(test_map);
	map->map[map->y_start][map->x_start] = '0';
	return (error);
}
