/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_pars3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:17:32 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/28 18:54:22 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_message(char *error)
{
	write(2, "Error : ", 8);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

int	check_infos(t_map_info *info)
{
	if (info->C == NULL || info->EA == NULL || info->F == NULL
		|| info->NO == NULL || info->SO == NULL || info->WE == NULL)
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
	if (!new_ptr)
		return (NULL);
	return (new_ptr);
}
