/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_pars3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:17:32 by hmimouni          #+#    #+#             */
/*   Updated: 2025/11/12 15:45:16 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_message(char *error)
{
	write(2, RED, sizeof(RED) - 1);
	write(2, "🚨 ERROR : ", 12);
	while (*error)
		write(2, error++, 1);
	write(2, "\n", 1);
	write(2, RESET, sizeof(RESET) - 1);
}

int	check_infos(t_map_info *info)
{
	if (info->ceiling == NULL || info->east == NULL || info->floor == NULL
		|| info->north == NULL || info->south == NULL || info->west == NULL)
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
		error_message("Mauvais nb d'args");
		return (FAILURE);
	}
	if (check_cub(av[1]))
	{
		error_message("Mauvais extension");
		return (FAILURE);
	}
	return (SUCCESS);
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	return (new_ptr);
}
