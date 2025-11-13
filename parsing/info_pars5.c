/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_pars5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:11:13 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/13 09:11:20 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_info_line(char *line, t_info_pars *pars, t_map_info *infos)
{
	pars->line_split = ft_split(line, ' ');
	if (!pars->line_split)
		return (1);
	if (pars_info(pars, infos))
		return (1);
	return (0);
}

int	parse_error(t_map_pars *map, t_map_info *infos, t_info_pars *pars,
		char *msg)
{
	error_message(msg);
	if (map->map)
		free_tab(map->map);
	if (pars)
		free_pars(pars);
	if (infos)
		free_info(infos);
	get_next_line(-1);
	return (1);
}
int	final_checks(t_map_info *infos, t_map_pars *map)
{
	if (map->position == 0)
	{
		error_message("map invalide: aucune position trouvée pour le joueur");
		free_info(infos);
		free_tab(map->map);
		return (1);
	}
	if (infos->count_info != 6 || check_infos(infos))
	{
		error_message(" Infos pas bon");
		free_tab(map->map);
		free_info(infos);
		return (1);
	}
	return (0);
}

int	parse_file(int fd, t_map_pars *map, t_map_info *infos, t_info_pars *pars)
{
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		line = remove_newline(line);
		if (!line)
			return (parse_error(map, infos, pars, "lecture ligne"));
		if (infos->count_info < 6)
		{
			if (parse_info_line(line, pars, infos))
			{
				free(line);
				// free_info(infos);
				parse_error(map, infos, pars,"parsing infos");
				return FAILURE;
			}	
		}
		else if ((!line[0] || !is_full_of_spaces(line)) && !map->map_started)
			;
		else if (!check_char(line, map) && !check_positions(map, line))
			add_line_to_map(map, line);
		else
			return (free(line), parse_error(map, infos, pars,
					" parsing map"));
		free(line);
		free_pars(pars);
	}
	return (0);
}