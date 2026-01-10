/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:25:35 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/10 19:42:20 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*remove_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
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

int	is_html_color(char *color)
{
	int	i;

	i = 1;
	if (color[0] != '#' || ft_strlen(color + 1) != 6)
		return (FAILURE);
	while (color[i])
	{
		if (!(color[i] >= '0' && color[i] <= '9') && !(color[i] >= 'A'
				&& color[i] <= 'F') && !(color[i] >= 'a' && color[i] <= 'f'))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
