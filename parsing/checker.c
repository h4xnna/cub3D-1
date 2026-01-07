/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:17:32 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/07 13:55:57 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_message(char *error)
{
	write(2, RED, sizeof(RED) - 1);
	write(2, "🚨 ERROR : ", 13);
	while (*error)
		write(2, error++, 1);
	write(2, "\n", 1);
	write(2, RESET, sizeof(RESET) - 1);
}

int	check_infos(t_map_info *info)
{
	if (info->east == NULL || info->north == NULL || info->south == NULL
		|| info->west == NULL || info->exit == NULL || info->skybox == NULL
		|| info->door == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	check_cub(char *str)
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
	if (HEIGHT < 20 || WIDTH <= 0 || HEIGHT > 1440 || WIDTH > 2560)
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
