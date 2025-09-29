/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_pars4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:53:12 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/29 15:08:02 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pars_info(t_info_pars *pars, t_map_info *infos)
{
	int i;

	if (!pars->line_split || (len_tab(pars->line_split) != 2
			&& pars->line_split[0]))
		return (FAILURE);
	if (!pars->line_split[0])
		return (SUCCESS);
	if (!is_direction(pars->line_split[0]) && !is_fichier(pars->line_split[1]))
	{
		fill_struct(infos, pars->line_split[0], pars->line_split[1]);
		infos->count_info += 1;
		return (SUCCESS);
	}
	else if (!ft_strcmp(pars->line_split[0], "F")
		|| !ft_strcmp(pars->line_split[0], "C"))
	{
		if (allouer_colors(pars, infos))
			return (FAILURE);
		pars->colors = ft_split(pars->line_split[1], ',');
		if (!pars->colors || len_tab(pars->colors) != 3)
		{
			if (pars->colors)
				free_tab(pars->colors);
			pars->colors = NULL;
			return (FAILURE);
		}
		i = 0;
		while (i < 3)
		{
			if (ft_atoi(pars->colors[i]) >= 0
				&& ft_atoll(pars->colors[i]) <= 255)
			{
				stock_colors(infos, pars, ft_atoll(pars->colors[i]), i);
				i++;
			}
			else
			{
				free_tab(pars->colors);
				pars->colors = NULL;
				;
				return (FAILURE);
			}
		}
	}
	infos->count_info += 1;
	return (SUCCESS);
}