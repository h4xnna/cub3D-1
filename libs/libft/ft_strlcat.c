/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:11:17 by hmimouni          #+#    #+#             */
/*   Updated: 2024/11/15 19:20:40 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;

	dlen = 0;
	if (dst)
		dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dlen >= siz)
		return (siz + slen);
	i = 0;
	while (i < siz - dlen - 1 && src[i])
	{
		dst[i + dlen] = src[i];
		i++;
	}
	if (dlen + i < siz)
		dst[i + dlen] = 0;
	return (slen + dlen);
}
