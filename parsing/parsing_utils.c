/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:25:35 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/07 12:37:55 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_strcmp(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i] && str2[i] && str[i] == str2[i])
		i++;
	return (str[i] - str2[i]);
}

char	*remove_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

int	is_fichier(char *path)
{
	if ((path[0] == '.' && path[1] == '/') || (path[0] == '.' && path[1] == '.'
			&& path[2] == '/'))
		return (SUCCESS);
	return (FAILURE);
}

int	is_prefix(char *str)
{
	if (!ft_strcmp(str, "NO") || !ft_strcmp(str, "EA") || !ft_strcmp(str, "SO")
		|| !ft_strcmp(str, "WE") || !ft_strcmp(str, "D") || !ft_strcmp(str, "L")
		|| !ft_strcmp(str, "skybox") || !ft_strcmp(str, "FT"))
		return (SUCCESS);
	return (FAILURE);
}
