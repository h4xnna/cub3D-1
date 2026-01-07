/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:07:05 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/07 12:34:12 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_struct(t_map_info *infos, char *prefix, char *path)
{
	if (!ft_strcmp(prefix, "NO") && !infos->north)
		infos->north = ft_strdup(path);
	else if (!ft_strcmp(prefix, "SO") && !infos->south)
		infos->south = ft_strdup(path);
	else if (!ft_strcmp(prefix, "EA") && !infos->east)
		infos->east = ft_strdup(path);
	else if (!ft_strcmp(prefix, "WE") && !infos->west)
		infos->west = ft_strdup(path);
	else if (!ft_strcmp(prefix, "L") && !infos->exit)
		infos->exit = ft_strdup(path);
	else if (!ft_strcmp(prefix, "D") && !infos->door)
		infos->door = ft_strdup(path);
	else if (!ft_strcmp(prefix, "skybox") && !infos->skybox)
		infos->skybox = ft_strdup(path);
}

void	stock_colors(t_map_info *infos, t_info_pars *pars, int nb, int i)
{
	if (!ft_strcmp(pars->line_split[0], "F"))
		infos->floor[i] = nb;
	if (!ft_strcmp(pars->line_split[0], "C"))
		infos->ceiling[i] = nb;
}

int	allouer_colors(t_info_pars *pars, t_map_info *infos)
{
	if (!ft_strcmp(pars->line_split[0], "F") && infos->floor == NULL)
	{
		infos->floor = malloc(sizeof(int) * 3);
		if (!infos->floor)
			return (FAILURE);
		return (SUCCESS);
	}
	else if (!ft_strcmp(pars->line_split[0], "C") && infos->ceiling == NULL)
	{
		infos->ceiling = malloc(sizeof(int) * 3);
		if (!infos->ceiling)
			return (FAILURE);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	remplir_colors(t_info_pars *pars, t_map_info *infos)
{
	int	i;

	i = 0;
	while (pars->colors[i])
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
