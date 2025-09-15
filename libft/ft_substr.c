/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:14:07 by hmimouni          #+#    #+#             */
/*   Updated: 2024/11/18 13:09:15 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	get_allocation(char const *s, unsigned int start, size_t len)
{
	if (start >= ft_strlen(s))
		return (0);
	if (len < ft_strlen(s + start))
		return (len);
	return (ft_strlen(s + start));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*out;
	unsigned int	i;

	i = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	out = ft_calloc(get_allocation(s, start, len) + 1, sizeof(char));
	if (!out)
		return (NULL);
	if (start >= ft_strlen(s))
		return (out);
	while (i < len && s[i + start])
	{
		out[i] = s[i + start];
		i++;
	}
	out[i] = '\0';
	return (out);
}
