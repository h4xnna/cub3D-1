/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:34:21 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/08 19:28:15 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	get_color_from_html(char *color)
{
	unsigned int	value;
	char			c;
	int				i;

	value = 0;
	i = 1;
	while (i <= 6)
	{
		c = color[i];
		value <<= 4;
		if (c >= '0' && c <= '9')
			value |= (c - '0');
		else if (c >= 'A' && c <= 'F')
			value |= (c - 'A' + 10);
		else if (c >= 'a' && c <= 'f')
			value |= (c - 'a' + 10);
		else
			return (0);
		i++;
	}
	return (value);
}

void	normalize_vector(double *x, double *y)
{
	double	length;

	length = sqrt((*x) * (*x) + (*y) * (*y));
	if (length != 0)
	{
		*x /= length;
		*y /= length;
	}
}

bool	is_walkable(char c)
{
	char	walkalbles[3];
	int		i;

	walkalbles[0] = '0';
	walkalbles[1] = 'L';
	walkalbles[2] = '\0';
	i = 0;
	while (walkalbles[i])
	{
		if (c == walkalbles[i])
			return (true);
		i++;
	}
	return (false);
}

double	get_time_seconds(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec + t.tv_usec / 1000000.0);
}

void	make_color_from_uint(unsigned int color, t_color *rgb)
{
	rgb->r = (color >> 16) & 0xFF;
	rgb->g = (color >> 8) & 0xFF;
	rgb->b = color & 0xFF;
}
