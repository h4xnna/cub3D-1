/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:10:23 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/13 09:10:43 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_structs(t_map_pars **map, t_map_info **infos, t_info_pars **pars, int *fd,
		t_data **data)
{
	*fd = 0;
	*map = ft_calloc(1, sizeof(t_map_pars));
	*infos = ft_calloc(1, sizeof(t_map_info));
	*pars = ft_calloc(1, sizeof(t_info_pars));
	*data = ft_calloc(1, sizeof(t_data));
	(*map)->map = malloc(sizeof(char *) * 1);
	if (!(*map)->map)
		return (1);
	(*map)->map[0] = NULL;
	return (0);
}