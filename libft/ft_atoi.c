/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:44:47 by hmimouni          #+#    #+#             */
/*   Updated: 2024/11/20 13:38:11 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspecial(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v')
		return (1);
	else if (c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	pass_chars(const char *s, int *i, int *minus)
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
		else if (ft_isspecial(s[*i]))
			*i += 1;
		else
			break ;
	}
	while (s[*i] && s[*i] == '0')
		*i += 1;
}

int	ft_atoi(const char *nptr)
{
	int	out;
	int	i;
	int	minus;

	i = 0;
	out = 0;
	minus = 1;
	pass_chars(nptr, &i, &minus);
	while (ft_isdigit(nptr[i]))
	{
		out *= 10;
		out += nptr[i] - '0';
		i++;
	}
	return (out * minus);
}
