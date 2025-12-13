/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:07:44 by hmimouni          #+#    #+#             */
/*   Updated: 2025/12/13 11:14:18 by hmimouni         ###   ########.fr       */
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
		error_message(" info");
		return (1);
	}
	while (i < 3)
	{
		printf("%i, ", tab[i]);
		i++;
	}
	return (0);
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
