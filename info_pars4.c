/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_pars4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:53:12 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/02 16:44:46 by hmimouni         ###   ########.fr       */
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

int	pars_info(t_info_pars *pars, t_map_info *infos)
{
	if (!pars->line_split || (len_tab(pars->line_split) != 2
			&& pars->line_split[0]))
		return (FAILURE);
	if (!pars->line_split[0])
		return (SUCCESS);
	if (!is_direction(pars->line_split[0]) && !is_fichier(pars->line_split[1]))
	{
		fill_struct(infos, pars->line_split[0], pars->line_split[1]);
		infos->count_info += 1;
		return (SUCCESS);
	}
	else if (!ft_strcmp(pars->line_split[0], "F")
		|| !ft_strcmp(pars->line_split[0], "C"))
	{
		if (allouer_colors(pars, infos))
			return (FAILURE);
		pars->colors = ft_split(pars->line_split[1], ',');
		if (!pars->colors || len_tab(pars->colors) != 3)
		{
			free_pars(pars);
			return (FAILURE);
		}
		if (remplir_colors(pars, infos))
			return (FAILURE);
	}
	infos->count_info += 1;
	return (SUCCESS);
}
// static int flood_fill_helper(t_map_pars *map,int x, int y)
// {
// 	if(x < 0 || y < 0 || !map->map[y] || !map->map[y][x])
// 		return(1);
// 	if(x == -1 || )
// 	flood_fill_helper(map->map, x - 1, y);
// 	flood_fill_helper(map->map, x + 1, y);
// 	flood_fill_helper(map->map, x, y + 1);
// 	flood_fill_helper(map->map, x, y - 1);

// }

int flood_fill_helper(t_map_pars *map, int x, int y)
{
    if (y < 0 || !map->map[y] || x < 0 || map->map[y][x] == '\0')
        return 0;
    if (map->map[y][x] == ' ')
        return 0;
    if (map->map[y][x] == '1' || map->map[y][x] == 'X')
        return 1;
    if (map->map[y][x] == 'N' || map->map[y][x] == 'S' ||
        map->map[y][x] == 'E' || map->map[y][x] == 'W') {
        map->map[y][x] = '0';
    }
    map->map[y][x] = 'X';
    if (!flood_fill_helper(map, x + 1, y)) return 0;
    if (!flood_fill_helper(map, x - 1, y)) return 0;
    if (!flood_fill_helper(map, x, y + 1)) return 0;
    if (!flood_fill_helper(map, x, y - 1)) return 0;
    return 1;
}

 int flood_fill(t_map_pars *map)
{
	int x = map->x_start;
	int y = map->y_start;
	
	if(flood_fill_helper(map, x, y))
		return(SUCCESS);
	return(FAILURE);
	
}
