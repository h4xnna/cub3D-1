/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:10:07 by hmimouni          #+#    #+#             */
/*   Updated: 2024/11/15 19:24:16 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*out;
	int		i;

	out = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!out)
		return (NULL);
	i = -1;
	while (++i, s[i])
		out[i] = s[i];
	out[i] = '\0';
	return (out);
}
