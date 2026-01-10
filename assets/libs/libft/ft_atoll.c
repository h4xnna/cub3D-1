/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:25:01 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/10 19:20:50 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pass_chars2(const char *s, int *i, int *minus)
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
