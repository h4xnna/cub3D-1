/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:26:04 by hmimouni          #+#    #+#             */
/*   Updated: 2025/11/08 14:39:40 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_char(char *line, t_map_pars *map)
{
	int	i;
	int	bouboule;

	i = 0;
	bouboule = 0;
	while (line[i])
	{
		if ((line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
				&& line[i] != 'W' && line[i] != 'D' && line[i] != 'L') && (line[i] != 48 && line[i] != 49
				&& line[i] != ' '))
			return (FAILURE);
		if (line[i] == 48 || line[i] == 49)
			bouboule = 1;
		map->map_started = 1;
		i++;
	}
	if (bouboule == 0)
		return (FAILURE);
	return (SUCCESS);
}

void	free_splif(char **out, int i)
{
	while (i > 0)
	{
		free(out[i]);
		i--;
	}
	free(out);
}

int	check_positions(t_map_pars *map, char *line)
{
	int	i;

	i = 0;
	skip_space(line);
	while (line[i])
	{
		if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'W'))
		{
			if (map->position == 0)
			{
				map->position = line[i];
				map->x_start = i;
				map->y_start = len_tab(map->map);
			}
			else
				return (error_message("invalide map: trop de position joueur"), FAILURE);
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
	if (!new_map)
		return (FAILURE);
	while (map->map[i])
	{
		new_map[i] = ft_strdup(map->map[i]);
		i++;
	}
	new_map[i] = ft_strdup(line);
	new_map[i + 1] = NULL;
	free_tab(map->map);
	if (!new_map[i])
		return (free_splif(new_map, i), FAILURE);
	map->map = new_map;
	return (SUCCESS);
}

int	is_full_of_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] !=  '\t')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	check_fd(int *fd, char **av)
{
	*fd = open((av[1]), O_RDONLY);
	if (*fd == -1)
	{
		error_message("Aucun fichier a ce nom");
		return (FAILURE);
	}
	return (SUCCESS);
}
