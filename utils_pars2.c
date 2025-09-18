/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:07:05 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/18 16:23:03 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_tab(int *tab)
{
	int i = 0;
	while(i < 3)
	{
		printf("%i, ", tab[i]);
		i++;
	}
}

void print_info(t_map_info info)
{
	printf("NORD : %s\n", info.NO);
	printf("SUD : %s\n", info.SO);
	printf("WEST : %s\n", info.WE);
	printf("EAST : %s\n", info.EA);
	printf("F : ");
	print_tab(info.F);
	printf("\nC : ");
	print_tab(info.C);
	printf("\ncount : %d\n", info.count_info);
}

void fill_struct(t_map_info *infos, char *direction, char *path)
{
	if(!ft_strcmp(direction, "NO"))
		infos->NO = ft_strdup(path);
	else if(!ft_strcmp(direction, "SO"))
		infos->SO = ft_strdup(path);
	else if(!ft_strcmp(direction, "EA"))
		infos->EA = ft_strdup(path);
	else if(!ft_strcmp(direction, "WE"))
		infos->WE = ft_strdup(path);
}


void stock_colors(t_map_info *infos, char *colors, int nb, int i)
{
	if(!ft_strcmp(colors, "F"))
		infos->F[i] = nb;
	if(!ft_strcmp(colors, "C"))
		infos->C[i] = nb;
}
int  allouer_colors(char *line_split, t_map_info *infos)
{
	if(!ft_strcmp(line_split, "F") && infos->F == NULL)
	{
		infos->F = malloc(sizeof(int) * 3); 
		return(SUCCESS);
	}
	else if(!ft_strcmp(line_split, "C") && infos->C == NULL) 
	{
		infos->C = malloc(sizeof(int) * 3);
		return(SUCCESS);
	}
	return(FAILURE);
}