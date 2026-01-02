/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pars1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:11:06 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/02 17:35:33 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_info_textures(t_map_info *info)
{
	if (info->east)
	{
		free(info->east);
		info->east = NULL;
	}
	if (info->south)
	{
		free(info->south);
		info->south = NULL;
	}
	if (info->west)
	{
		free(info->west);
		info->west = NULL;
	}
	if (info->north)
	{
		free(info->north);
		info->north = NULL;
	}
}

static void	free_info_colors(t_map_info *info)
{
	if (info->ceiling)
	{
		free(info->ceiling);
		info->ceiling = NULL;
	}
	if (info->floor)
	{
		free(info->floor);
		info->floor = NULL;
	}
}

void	free_info(t_map_info *info)
{
	free_info_textures(info);
	free_info_colors(info);
	free(info);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_pars(t_info_pars *pars)
{
	if (pars->line_split)
		free_tab(pars->line_split);
	pars->line_split = NULL;
	if (pars->colors)
		free_tab(pars->colors);
	pars->colors = NULL;
}
