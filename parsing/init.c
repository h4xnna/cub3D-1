/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:10:23 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/13 11:19:00 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_structs(t_map_pars **map, t_map_info **infos,
		t_info_pars **pars, int *fd,
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

// int	init_structs(t_init *init)
// {
// 	*(init->fd) = 0;
// 	*(init->map) = ft_calloc(1, sizeof(t_map_pars));
// 	*(init->infos) = ft_calloc(1, sizeof(t_map_info));
// 	*(init->pars)= ft_calloc(1, sizeof(t_info_pars));
// 	*(init->data)= ft_calloc(1, sizeof(t_data));
// 	if (!*(init->map) || !*(init->infos)
// 		|| !*(init->pars) || !*(init->data))
// 		return (FAILURE);
// 	(*(init->map))->map = malloc(sizeof(char *));
// 	if (!(*(init->map))->map)
// 		return (FAILURE);
// 	(*(init->map))->map[0] = NULL;
// 	return (SUCCESS);
// }

int	skip_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	check_fd(int *fd, char **av)
{
	*fd = open((av[1]), O_RDONLY);
	if (*fd == -1)
	{
		error_message("Aucun fichier a ce nom");
		return (FAILURE);
	}
	return (SUCCESS);
}
