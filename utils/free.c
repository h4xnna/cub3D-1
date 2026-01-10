/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:11:06 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/08 19:24:33 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static void	free_info_textures(t_map_info *info)
{
	if (info->east)
		free_and_null((void **)&info->east);
	if (info->south)
		free_and_null((void **)&info->south);
	if (info->west)
		free_and_null((void **)&info->west);
	if (info->north)
		free_and_null((void **)&info->north);
	if (info->exit)
		free_and_null((void **)&info->exit);
	if (info->door)
		free_and_null((void **)&info->door);
	if (info->skybox)
		free_and_null((void **)&info->skybox);
	if (info->floor)
		free_and_null((void **)&info->floor);
}

void	free_info(t_map_info *info)
{
	free_info_textures(info);
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
