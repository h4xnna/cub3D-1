/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:25:35 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/10 19:26:31 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	is_file(char *path)
{
	if ((path[0] == '.' && path[1] == '/') || (path[0] == '.' && path[1] == '.'
			&& path[2] == '/'))
		return (SUCCESS);
	return (FAILURE);
}

int	is_direction(char *str)
{
	if (!ft_strcmp(str, "NO") || !ft_strcmp(str, "EA") || !ft_strcmp(str, "SO")
		|| !ft_strcmp(str, "WE"))
		return (SUCCESS);
	return (FAILURE);
}

static int	count_coma(char *line)
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

int	pars_info(t_info_pars *pars, t_map_info *infos)
{
	if (!pars->line_split || (len_tab(pars->line_split) != 2
			&& pars->line_split[0]))
		return (FAILURE);
	if (!pars->line_split[0])
		return (SUCCESS);
	if (!is_direction(pars->line_split[0]) && !is_file(pars->line_split[1]))
	{
		fill_struct(infos, pars->line_split[0], pars->line_split[1]);
		infos->count_info += 1;
		return (SUCCESS);
	}
	else if (!ft_strcmp(pars->line_split[0], "F")
		|| !ft_strcmp(pars->line_split[0], "C"))
	{
		if (allocate_colors(pars, infos) || count_coma(pars->line_split[1]))
			return (FAILURE);
		pars->colors = ft_split(pars->line_split[1], ',');
		if (!pars->colors || len_tab(pars->colors) != 3)
			return (FAILURE);
		if (fill_colors(pars, infos))
			return (FAILURE);
	}
	infos->count_info += 1;
	return (SUCCESS);
}
