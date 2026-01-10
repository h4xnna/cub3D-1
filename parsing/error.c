/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:31:06 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/10 19:31:58 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	error_message(char *error)
{
	write(2, RED, sizeof(RED) - 1);
	write(2, "🚨 ERROR : ", 13);
	while (*error)
		write(2, error++, 1);
	write(2, "\n", 1);
	write(2, RESET, sizeof(RESET) - 1);
}

int	parse_error(char *msg)
{
	error_message(msg);
	return (FAILURE);
}
