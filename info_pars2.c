/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:07:05 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/25 17:36:31 by hmimouni         ###   ########.fr       */
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

void print_char(char **str)
{
	int i = 0;
	int j = 0;
	
	while(str[j])
	{
		while(str[j][i])
		{
			write(1, &str[j][i], 1);
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
}

void print_info(t_map_info info, t_map_pars map)
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
	print_char(map.map);
	printf("position map: %d\n", map.position);
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


void stock_colors(t_map_info *infos, t_info_pars *pars , int nb, int i)
{
	if(!ft_strcmp(pars->line_split[0], "F"))
		infos->F[i] = nb;
	if(!ft_strcmp(pars->line_split[0], "C"))
		infos->C[i] = nb;
}
int  allouer_colors(t_info_pars *pars, t_map_info *infos)
{
	if(!ft_strcmp(pars->line_split[0], "F") && infos->F == NULL)
	{
		infos->F = malloc(sizeof(int) * 3); 
		if(!infos->F)
			return FAILURE;
		return(SUCCESS);
	}
	else if(!ft_strcmp(pars->line_split[0], "C") && infos->C == NULL) 
	{
		infos->C = malloc(sizeof(int) * 3);
		if(infos->C)
			return FAILURE;
		return(SUCCESS);
	}
	return(FAILURE);
}