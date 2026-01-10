/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:17:32 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/10 19:30:57 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_infos(t_map_info *info)
{
	if (info->east == NULL || info->north == NULL || info->south == NULL
		|| info->west == NULL || info->exit == NULL || info->skybox == NULL
		|| info->door == NULL || info->floor == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static int	check_cub(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) < 5)
		return (FAILURE);
	while (str[i + 4])
		i++;
	if (ft_strncmp(&str[i], ".cub", 4) && str)
		return (FAILURE);
	return (SUCCESS);
}

int	final_checks(t_map_info *infos, t_map_pars *map)
{
	if (map->position == 0)
		return (parse_error("No starting position"));
	if (infos->count_info != 8 || check_infos(infos))
		return (parse_error("Not enough infos, or wrong ones"));
	return (SUCCESS);
}

int	checks_args(int ac, char **av)
{
	if (ac != 2)
	{
		error_message("Wrong number of arguments");
		return (FAILURE);
	}
	if (check_cub(av[1]))
	{
		error_message("Wrong file extension");
		return (FAILURE);
	}
	if (HEIGHT < 20 || WIDTH <= 20 || HEIGHT > 1440 || WIDTH > 2560)
	{
		error_message("Wrong window size");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_fd(int *fd, char **av)
{
	*fd = open((av[1]), O_RDONLY);
	if (*fd == -1)
	{
		error_message("No such file");
		return (FAILURE);
	}
	return (SUCCESS);
}
