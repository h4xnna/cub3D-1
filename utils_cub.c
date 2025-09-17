/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:25:35 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/17 14:43:59 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int len_tab(char **tab)
{
	int i = 0;
	
	while(tab[i])
	{
		// printf("tableau %d : %s \n", i, tab[i]);		
		i++;
	}

	return(i);
}
int ft_strcmp(char *str, char *str2)
{
	int i = 0;

	while (str[i] && str2[i] && str[i] == str2[i])
		i++;
	return (str[i] - str2[i]);
}
char *remove_newline(char *line)
{
    int len = ft_strlen(line); 

    if (len > 0 && line[len - 1] == '\n') 
        line[len - 1] = '\0'; 
    return (line);
}