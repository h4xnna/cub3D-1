/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:50:08 by hmimouni          #+#    #+#             */
/*   Updated: 2024/11/15 19:21:56 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*out;

	if (size > 0)
		if (MAX_INT / size < nmemb)
			return (NULL);
	out = malloc(nmemb * size);
	if (!out)
		return (NULL);
	ft_bzero(out, nmemb * size);
	return (out);
}
