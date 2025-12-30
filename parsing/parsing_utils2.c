/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:07:44 by hmimouni          #+#    #+#             */
/*   Updated: 2025/12/30 10:16:54 by pacda-si         ###   ########.fr       */
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

int	ft_isspecial2(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v')
		return (1);
	else if (c == '\f' || c == '\r')
		return (1);
	return (0);
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

long long	ft_atoll(const char *nptr)
{
	long long	out;
	int			i;
	int			minus;

	i = 0;
	out = 0;
	minus = 1;
	pass_chars2(nptr, &i, &minus);
	while (ft_isdigit(nptr[i]))
	{
		out *= 10;
		out += nptr[i] - '0';
		i++;
	}
	return (out * minus);
}
