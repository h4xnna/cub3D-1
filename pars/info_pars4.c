/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_pars4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:53:12 by hmimouni          #+#    #+#             */
/*   Updated: 2025/11/12 15:19:26 by pacda-si         ###   ########.fr       */
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
int count_coma(char *line)
{
	int i = 0;
	int j = 0;
	int len = ft_strlen(line);
	while(i < len)
	{
		if(line[i] == ',')
			j++;
		i++;
	}
	if(j != 2)	
		return(FAILURE);
	return(SUCCESS);
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
		if(count_coma(pars->line_split[1]))
			return(FAILURE);
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

int flood_fill_helper(char **map, int x, int y)
{
    if (y < 0 || !map[y] || x < 0 || map[y][x] == '\0')
        return 0;
    if (map[y][x] == ' ')
        return 0;
    if (map[y][x] == '1' || map[y][x] == 'X')
        return 1;
    if (map[y][x] == 'N' || map[y][x] == 'S' ||
        map[y][x] == 'E' || map[y][x] == 'W' || map[y][x] == 'D' || map[y][x] == 'L')
	{
        map[y][x] = '0';
    }
    map[y][x] = 'X';
    if (!flood_fill_helper(map, x + 1, y)) return 0;
    if (!flood_fill_helper(map, x - 1, y)) return 0;
    if (!flood_fill_helper(map, x, y + 1)) return 0;
    if (!flood_fill_helper(map, x, y - 1)) return 0;
    return 1;
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

 int flood_fill(t_map_pars *map)
{
	int x = map->x_start;
	int y = map->y_start;
	int error;
	
	char **test_map;
	error = 0;

	test_map = clone_map(map->map);
	if(!flood_fill_helper(test_map, x, y))
		error = 1;
	free_tab(test_map);
	map->map[map->y_start][map->x_start] = '0';
	return (error);
	
}
