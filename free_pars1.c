/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pars1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:11:06 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/28 14:35:38 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_info(t_map_info *info)
{
	if(info->EA)
		free(info->EA), info->EA = NULL;
	if(info->SO)
		free(info->SO), info->SO = NULL;
	if(info->WE)
		free(info->WE), info->WE = NULL;
	if(info->C)
		free(info->C), info->C = NULL;
	if(info->F)
		free(info->F), info->F = NULL;
	if(info->NO)
		free(info->NO), info->NO = NULL;
}
void free_tab(char **tab)
{
	int i = 0;
	if(!tab)
		return;
	while(tab[i])
	{
		free(tab[i]);
		i++;	
	}
	free(tab);
}

void free_pars(t_info_pars *pars)
{	
	if(pars->line_split)
			free_tab(pars->line_split);
		pars->line_split = NULL;
		if(pars->colors)
			free_tab(pars->colors);
		pars->colors = NULL;
}