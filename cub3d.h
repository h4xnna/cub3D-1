/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:24:03 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/23 20:22:28 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "gnl/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

#define FAILURE 1
#define SUCCESS 0


typedef struct s_pars
{
	char **line_split;
	char **colors;
	
}	t_pars;

typedef struct s_map_info
{
	char *SO;
	char *WE;
	char *EA;
	char *NO;
	int *F;
	int *C;
	int count_info;
}		t_map_info;

//utils_pars1
int len_tab(char **tab);
char *remove_newline(char *line);
int ft_strcmp(char *str, char *str2);
int is_fichier(char *path);
int is_direction(char *str);

//utils_pars2
void print_info(t_map_info info);
void fill_struct(t_map_info *infos, char *direction, char *path);
void stock_colors(t_map_info *infos, t_pars *pars , int nb, int i);
int  allouer_colors(t_pars *pars, t_map_info *infos);

//utils_pars3
void error_message(char *error);
int check_infos(t_map_info *info);
 // struct pars : line split etc..
 // struct game : info ...