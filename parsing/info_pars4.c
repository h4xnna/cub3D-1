/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_pars4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:53:12 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/04 13:17:13 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	remplir_colors(t_info_pars *pars, t_map_info *infos)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ft_atoll(pars->colors[i]) >= 0 && ft_atoll(pars->colors[i]) <= 255)
		{
			stock_colors(infos, pars, ft_atoll(pars->colors[i]), i);
			i++;
		}
		else
		{
			free_tab(pars->colors);
			pars->colors = NULL;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	count_coma(char *line)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (line[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		return (FAILURE);
	return (SUCCESS);
}

int	flood_fill_helper(char **map, int x, int y)
{
	if (y < 0 || !map[y] || x < 0 || map[y][x] == '\0')
		return (0);
	if (map[y][x] == ' ')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (1);
	if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
		|| map[y][x] == 'W' || map[y][x] == 'D' || map[y][x] == 'L')
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

char	**clone_map(char **map)
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
	if (!test_map)
	{
		error_message("Malloc failed for flood fill");
		return (1);
	}
	if (!flood_fill_helper(test_map, x, y))
		error = 1;
	free_tab(test_map);
	map->map[map->y_start][map->x_start] = '0';
	return (error);
}
