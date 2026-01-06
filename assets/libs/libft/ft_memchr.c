/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:52:43 by hmimouni          #+#    #+#             */
/*   Updated: 2024/11/15 19:23:29 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	void	*out;
	size_t	i;

	i = 0;
	out = NULL;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
		{
			out = &((unsigned char *)s)[i];
			break ;
		}
		i++;
	}
	return (out);
}
