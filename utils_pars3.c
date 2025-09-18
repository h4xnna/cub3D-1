/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:17:32 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/18 15:19:55 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void error_message(char *error)
{
	write(2, "Error : ", 8);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

int check_infos(t_map_info *info)
{
    if(info->C == NULL || info->EA == NULL || info->F == NULL || info->NO == NULL
       || info->SO == NULL || info->WE == NULL)
        return (FAILURE);
    return (SUCCESS);
}