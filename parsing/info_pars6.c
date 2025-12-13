/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_pars6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:27:05 by hmimouni          #+#    #+#             */
/*   Updated: 2025/12/13 10:54:32 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	pars_info_else(t_info_pars *pars, t_map_info *infos)
{
	if (allouer_colors(pars, infos))
		return (FAILURE);
	if (count_coma(pars->line_split[1]))
		return (FAILURE);
	pars->colors = ft_split(pars->line_split[1], ',');
	if (!pars->colors || len_tab(pars->colors) != 3)
	{
		free_pars(pars);
		return (FAILURE);
	}
	if (remplir_colors(pars, infos))
		return (FAILURE);
	return (SUCCESS);
}

int	pars_info(t_info_pars *pars, t_map_info *infos)
{
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
		pars_info_else(pars, infos);
	infos->count_info += 1;
	return (SUCCESS);
}
