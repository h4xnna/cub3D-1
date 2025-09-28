/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_pars2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:07:05 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/28 14:34:40 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int print_tab(int *tab)
{
	int i = 0;
	if (!tab)
	{
		error_message("error : info");
		return(1);
	}
	while(i < 3)
	{
		printf("%i, ", tab[i]);
		i++;
	}
	return(0);
}

void print_char(char **str)
{
	int j = 0;
	
	if (!str)
		return ;
	while(str[j])
	{
		printf("%s\n", str[j]);
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
	if(info.F)
		print_tab(info.F);
	printf("\nC : ");
	if(info.C)
		print_tab(info.C);
	printf("\ncount : %d\n", info.count_info);
	print_char(map.map);
	printf("position map: %c\n", map.position);
	printf("start_x = %i\n", map.x_start);
	printf("start_y = %i\n", map.y_start);

	
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
		if(!infos->C)
			return FAILURE;
		return(SUCCESS);
	}
	return(FAILURE);
}