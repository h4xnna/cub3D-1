/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:04:09 by hmimouni          #+#    #+#             */
/*   Updated: 2024/11/20 13:39:21 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	get_points(int *sp, int *ep, char const *s, char const *set)
{
	int	i;

	i = 0;
	*sp = 0;
	*ep = 0;
	while (s[i])
	{
		if (!is_in_set(s[i], set))
		{
			*sp = i;
			break ;
		}
		i++;
	}
	i = ft_strlen(s) - 1;
	while (i > 0)
	{
		if (!is_in_set(s[i], set))
		{
			*ep = i + 1;
			break ;
		}
		i--;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*out;
	int		startingp;
	int		endingp;
	int		i;

	get_points(&startingp, &endingp, s1, set);
	out = ft_calloc((endingp - startingp) + 1, sizeof(char));
	if (out)
	{
		i = startingp;
		while (i < endingp && endingp > 0)
		{
			out[i - startingp] = s1[i];
			i++;
		}
		out[i - startingp] = 0;
	}
	else
		return (NULL);
	return (out);
}
