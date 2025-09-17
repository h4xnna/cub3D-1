/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:07:05 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/17 19:17:12 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_info(t_map_info info)
{
	printf("NORD : %s\n", info.NO);
	printf("SUD : %s\n", info.SO);
	printf("WEST : %s\n", info.WE);
	printf("EAST : %s\n", info.EA);
	printf("count : %d\n", info.count_info);
}
void fill_struct(t_map_info *infos, char *direction, char *path)
{
	if(ft_strcmp(direction, "NO"))
		infos->NO = path;
	if(ft_strcmp(direction, "SO"))
		infos->SO = path;
	if(ft_strcmp(direction, "EA"))
		infos->EA = path;
	if(ft_strcmp(direction, "WE"))
		infos->WE = path;
}

// void stock_colors(t_map_info *infos, char colors, int *nb)
// {
// 	if(ft_strcmp(colors, "F"))
// 		infos->F =path;
// 	if(ft_strcmp(direction, "C"))
// 		infos->C = path;
// }