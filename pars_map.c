/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:26:04 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/28 14:46:54 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_positions(t_map_pars *map, char *line)
{
	int	x;
	int	i;

	i = 0;
	x = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W') || (line[i] != 48 && line[i] != 49 && line[i] != ' '))
		{
			if (map->check_pos == 0)
			{
				map->position = line[i];
				map->check_pos = 1;
				map->x_start = i;
				map->y_start = len_tab(map->map);
			}
			else
			{
				error_message("invalide map: trop de position pour le joeur");
				return (FAILURE);
			}
		}
		i++;
	}
	return (SUCCESS);
}



int	add_line_to_map(t_map_pars *map, char *line)
{
	char	**new_map;
	int		i;
	int		map_len;

	i = 0;
	if (!map || !line)
		return (FAILURE);
	map_len = len_tab(map->map);
	new_map = malloc(sizeof(char *) * (map_len + 2));
	if(!new_map)
		return(FAILURE);
	while(map->map[i])
	{
		new_map[i] = ft_strdup(map->map[i]);
		i++;
	}
	new_map[i] = ft_strdup(line);
	new_map[i+ 1] = NULL;
	free_tab(map->map);
	if(!new_map[i])
		return(FAILURE);
	map->map = new_map;
	return(SUCCESS);
	
}
// int add_line_to_map(t_map_pars *map, char *line)
// {
//     char **new_map;
//     int count = 0;
// 	int j = 0;
// 	int i = 0;

//     if (!map || !line)
//         return (FAILURE);

//     while (map->map && map->map[count])
//         count++;
//     new_map = malloc(sizeof(char *) * (count + 1));
//     if (!new_map)
// 		return (FAILURE);
// 	while(i < count )
// 	{
// 		new_map[i] = map->map[i][j];
// 		i++;
// 	}
//     new_map[count] = ft_strdup(line);
//     if(!new_map[count])
//     {
//         free(new_map);
//         return (FAILURE);
//     }
//     new_map[count] = NULL;
//     if (map->map)
//         free(map->map);
//     map->map = new_map;

//     return (SUCCESS);
// }
