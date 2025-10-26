/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_pars2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:07:05 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/26 17:21:26 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_info(t_map_info info, t_map_pars map)
{
	printf("NORD : %s\n", info.north);
	printf("SUD : %s\n", info.south);
	printf("WEST : %s\n", info.west);
	printf("EAST : %s\n", info.east);
	printf("F : ");
	if (info.floor)
		print_tab(info.floor);
	printf("\nC : ");
	if (info.ceiling)
		print_tab(info.ceiling);
	printf("\ncount : %d\n", info.count_info);
	print_char(map.map);
	printf("position map: %c\n", map.position);
	printf("start_x = %i\n", map.x_start);
	printf("start_y = %i\n", map.y_start);
}

void	fill_struct(t_map_info *infos, char *direction, char *path)
{
	if (!ft_strcmp(direction, "NO") && !infos->north)
		infos->north = ft_strdup(path);
	else if (!ft_strcmp(direction, "SO") && !infos->south)
		infos->south = ft_strdup(path);
	else if (!ft_strcmp(direction, "EA") && !infos->east)
		infos->east = ft_strdup(path);
	else if (!ft_strcmp(direction, "WE") && !infos->west)
		infos->west = ft_strdup(path);
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
