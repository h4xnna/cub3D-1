/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_pars1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:25:35 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/28 18:48:54 by hmimouni         ###   ########.fr       */
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

int	is_direction(char *str)
{
	if (!ft_strcmp(str, "NO") || !ft_strcmp(str, "EA") || !ft_strcmp(str, "SO")
		|| !ft_strcmp(str, "WE"))
		return (SUCCESS);
	return (FAILURE);
}
