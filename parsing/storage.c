/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:07:05 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/08 17:33:43 by pacda-si         ###   ########.fr       */
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
	else if (!ft_strcmp(prefix, "sky") && !infos->skybox)
	{
		infos->skybox = ft_strdup(path);
		infos->has_skybox = true;
	}
	else if (!ft_strcmp(prefix, "floor") && !infos->floor)
	{
		infos->floor = ft_strdup(path);
		infos->has_floor = true;
	}
}
