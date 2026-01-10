/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:07:44 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/10 16:57:06 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_isspecial2(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v')
		return (1);
	else if (c == '\f' || c == '\r')
		return (1);
	return (0);
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

void	pass_chars2(const char *s, int *i, int *minus)
{
	while (s[*i])
	{
		if (s[*i] == '+')
		{
			*i += 1;
			break ;
		}
		else if (s[*i] == '-')
		{
			*i += 1;
			*minus *= -1;
			break ;
		}
		else if (ft_isspecial2(s[*i]))
			*i += 1;
		else
			break ;
	}
	while (s[*i] && s[*i] == '0')
		*i += 1;
}
