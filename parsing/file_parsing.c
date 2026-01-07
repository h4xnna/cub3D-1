/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:38:55 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/07 12:16:51 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_info_line(char *line, t_info_pars *pars, t_map_info *infos)
{
	pars->line_split = ft_split(line, ' ');
	if (!pars->line_split)
		return (FAILURE);
	if (!pars->line_split || (len_tab(pars->line_split) != 2
			&& pars->line_split[0]))
		return (FAILURE);
	if (!pars->line_split[0])
		return (SUCCESS);
	if (pars_info(pars, infos))
		return (FAILURE);
	return (SUCCESS);
}

int	parse_error(char *msg)
{
	error_message(msg);
	return (FAILURE);
}

int	final_checks(t_map_info *infos, t_map_pars *map)
{
	if (map->position == 0)
		return (parse_error("No starting position"));
	if (infos->count_info != 6 || check_infos(infos))
		return (parse_error("Not enough infos, or wrong ones"));
	return (SUCCESS);
}

int	parse_file(int fd, t_map_pars *map, t_map_info *infos, t_info_pars *pars)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		line = remove_newline(line);
		if (!line)
			return (parse_error("Line reading failed"));
		if (infos->count_info < 6)
		{
			if (parse_info_line(line, pars, infos))
				return (free(line), parse_error("Info parsing failed"));
		}
		else if ((!line[0] || !is_full_of_spaces(line)) && !map->map_started)
			;
		else if (!check_char(line, map) && !check_positions(map, line))
			add_line_to_map(map, line);
		else
			return (free(line), parse_error("Map parsing"));
		free(line);
		free_pars(pars);
		line = get_next_line(fd);
	}
	map->height = len_tab(map->map);
	return (0);
}
