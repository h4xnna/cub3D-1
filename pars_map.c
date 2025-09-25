/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:26:04 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/25 17:30:53 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_positions(t_map_pars *map, char *line)
{
    int x ;
	int y;
	int i;

	i = 0;
	x = 0;
    y = 0;

	while(line[i] == ' ')
		i++;
    while (map->map[y])
    {
        while (map->map[y][x])
        {
			if(map->map[x][y] == ' ')
			{
		       error_message("invalide map : vide dans la map");
				return(FAILURE);
			}
            if (map->map[y][x] == 'N' || map->map[y][x] == 'S' ||
                map->map[y][x] == 'E' || map->map[y][x] == 'W')
            {
                if (map->check_pos == 0)
                {
                    map->position = map->map[y][x];
                    map->check_pos = true;
                }
                else
                {
                    error_message("invalide map: trop de position pour le joeur");
                    return (FAILURE);
                }
            }
            x++;
        }
        y++;
	}
    if (map->check_pos == false)
    {
        error_message("map invalide: aucune position trouve pour le joeur ");
        return (FAILURE);
    }
    return SUCCESS;
}
int add_line_to_map(t_map_pars *map, char *line)
{
	static int n = 0;
	static int count = 0;
	char **new_map;
	int i;

	if (!line || !map)
		return FAILURE;

	if (n == 0)
	{
		n = 1;
		map->map = malloc(sizeof(char *) * (n + 1)); 
		if (!map->map)
			return FAILURE;
	}
	if (count >= n)
	{
		n *= 2;
		new_map = malloc(sizeof(char *) * (n + 1));
		if (!new_map)
			return FAILURE;
		
		i = 0;
		while (i < count)
		{
			new_map[i] = map->map[i]; 
			i++;
		}
		free(map->map);
		map->map = new_map;
	}
	map->map[count++] = ft_strdup(line);
	map->map[count] = NULL;
	return SUCCESS;
}
