/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_pars1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:07:44 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/28 18:50:12 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_char(char **str)
{
	int	j;

	j = 0;
	if (!str)
		return ;
	while (str[j])
	{
		printf("%s\n", str[j]);
		j++;
	}
}
int	print_tab(int *tab)
{
	int	i;

	i = 0;
	if (!tab)
	{
		error_message("error : info");
		return (1);
	}
	while (i < 3)
	{
		printf("%i, ", tab[i]);
		i++;
	}
	return (0);
}