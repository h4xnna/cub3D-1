/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:38:55 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/10 19:40:56 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_prefix(char *str)
{
	if (!ft_strcmp(str, "NO") || !ft_strcmp(str, "EA") || !ft_strcmp(str, "SO")
		|| !ft_strcmp(str, "WE") || !ft_strcmp(str, "D") || !ft_strcmp(str, "L")
		|| !ft_strcmp(str, "sky") || !ft_strcmp(str, "floor"))
		return (SUCCESS);
	return (FAILURE);
}

static int	is_file(char *path)
{
	if ((path[0] == '.' && path[1] == '/') || (path[0] == '.' && path[1] == '.'
			&& path[2] == '/'))
		return (SUCCESS);
	return (FAILURE);
}

int	pars_info(t_info_pars *pars, t_map_info *infos)
{
	if (!is_prefix(pars->line_split[0]) && !is_file(pars->line_split[1]))
		fill_struct(infos, pars->line_split[0], pars->line_split[1]);
	if (!infos->skybox && !ft_strcmp(pars->line_split[0], "sky")
		&& is_html_color(pars->line_split[1]) == SUCCESS)
	{
		infos->skybox = ft_strdup(pars->line_split[1]);
		infos->has_skybox = false;
	}
	if (!infos->floor && !ft_strcmp(pars->line_split[0], "floor")
		&& is_html_color(pars->line_split[1]) == SUCCESS)
	{
		infos->floor = ft_strdup(pars->line_split[1]);
		infos->has_floor = false;
	}
	infos->count_info += 1;
	return (SUCCESS);
}

static int	parse_info_line(char *line, t_info_pars *pars, t_map_info *infos)
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

int	parse_file(int fd, t_map_pars *map, t_map_info *infos, t_info_pars *pars)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		line = remove_newline(line);
		if (!line)
			return (parse_error("Line reading failed"));
		if (infos->count_info < 8)
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
