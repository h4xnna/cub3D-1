/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:10:23 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/02 18:33:40 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
