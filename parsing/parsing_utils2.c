/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:07:44 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/10 19:23:00 by pacda-si         ###   ########.fr       */
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

int	is_full_of_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspecial2(line[i]) == 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

char	*remove_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}
