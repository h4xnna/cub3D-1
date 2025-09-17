/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:24:03 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/17 14:15:56 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "gnl/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

#define FAILURE 1
#define SUCCESS 0


typedef struct map_s
{
	int fd;
	
}		map_t;

int len_tab(char **tab);
int ft_strcmp(char *str, char *str2);
char *remove_newline(char *line);
