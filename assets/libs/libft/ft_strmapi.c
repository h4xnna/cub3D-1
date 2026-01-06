/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:12:47 by hmimouni          #+#    #+#             */
/*   Updated: 2024/11/15 19:28:21 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*out;
	unsigned int	i;

	out = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (out)
	{
		i = 0;
		while (s[i])
		{
			out[i] = f(i, s[i]);
			i++;
		}
	}
	return (out);
}
