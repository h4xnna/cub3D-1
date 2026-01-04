/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:13:21 by hmimouni          #+#    #+#             */
/*   Updated: 2024/11/15 19:29:36 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*out;

	i = 0;
	j = 0;
	out = (char *)big;
	if (!ft_strlen(little))
		return (out);
	if (!big && !len)
		return (NULL);
	while (big[i] && i + j < len)
	{
		j = 0;
		out = &((char *)big)[i];
		while (little[j] == big[i + j] && i + j < len)
		{
			j++;
			if (!little[j] || i + j > len)
				return (out);
		}
		i++;
	}
	return (NULL);
}
