/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/25 17:42:08 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void free_pars(t_info_pars *pars)
{	
	if(pars->line_split)
			free_split(pars->line_split, len_tab(pars->line_split));
		pars->line_split = NULL;
		if(pars->colors)
			free_split(pars->colors, len_tab(pars->colors));
		pars->colors = NULL;
}
void free_all(t_map_info *info)
{
	if(info->EA)
		free(info->EA), info->EA = NULL;
	if(info->SO)
		free(info->SO), info->SO = NULL;
	if(info->WE)
		free(info->WE), info->WE = NULL;
	if(info->C)
		free(info->C), info->C = NULL;
	if(info->F)
		free(info->F), info->F = NULL;
	if(info->NO)
		free(info->NO), info->NO = NULL;
}

int check_map(t_info_pars *pars, t_map_info *infos)
{
	int i;

	if (!pars->line_split || (len_tab(pars->line_split) != 2 && pars->line_split[0]))
		return (FAILURE);
	if (!pars->line_split[0])
		return (SUCCESS);
	if (!is_direction(pars->line_split[0]) && !is_fichier(pars->line_split[1]))
	{
		fill_struct(infos, pars->line_split[0], pars->line_split[1]);
		infos->count_info += 1; 
		return (SUCCESS);
	}
	else if (!ft_strcmp(pars->line_split[0], "F") || !ft_strcmp(pars->line_split[0], "C"))
	{
		if(allouer_colors(pars, infos))
			return(FAILURE);
		pars->colors = ft_split(pars->line_split[1], ',');
		if (!pars->colors || len_tab(pars->colors) != 3)
		{
			if (pars->colors)
				free_split(pars->colors, len_tab(pars->colors));
			pars->colors = NULL;
			return (FAILURE);
		}
		i = 0;
		while (i < 3)
		{
			if (ft_atoi(pars->colors[i]) >= 0 && ft_atoi(pars->colors[i]) <= 255 )
			{
				stock_colors( infos, pars, ft_atoi(pars->colors[i]), i);
				i++;
			}
			else 
			{
				free_split(pars->colors, len_tab(pars->colors));
				pars->colors = NULL;;
				return(FAILURE);
			}
		}
	}
	infos->count_info += 1; 
	return(SUCCESS);
}


int	main(int ac, char **av)
{
	int			fd;
	char		*line;
	t_map_info	infos;
	t_info_pars		pars;
	t_map_pars		map;
	
	ft_bzero(&map, sizeof(t_map_pars));
	ft_bzero(&infos, sizeof(t_map_info));
	ft_bzero(&pars, sizeof(t_info_pars));

	if(checks_args(ac, av))
	{
		free_all(&infos);
		free_pars(&pars);
		return(FAILURE);
	}
	fd = open((av[1]), O_RDONLY);
	if (fd == -1)
	{
		error_message("Aucun fichier a ce nom");
		return (FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		line = remove_newline(line);
		if(!line)
		{
			error_message("NTM");
			free(line);
			break;
		}
		 if (add_line_to_map(&map, line) == FAILURE)
   		{
			printf("yo bb");
    	}
		pars.line_split = ft_split(line, ' ');
		if (!pars.line_split)
		{
		    free(line);
		    error_message("Erreur split");
		    break;
		}
		if(check_map(&pars, &infos))
		{
			free(line);
			free_pars(&pars);
			error_message("NTM");
			break;
		}
		// printf("%s\n", line);
		free(line);
		free_pars(&pars);
		
	}
	if(infos.count_info != 6 || check_infos(&infos))
	{
		error_message("Infos pas bon");
		free_all(&infos);
		free_pars(&pars);
		return (FAILURE);
	}
	print_info(infos, map);
	free_all(&infos);
	// free_pars(&pars);
	close(fd);
	return (SUCCESS);
}
//1 = mur
//0 = sol
//' ' = vide
//N , S, E, W =  orientation
//
//ignorer lignes vides												OK
//refuser lignes vides milieu de carte								OK
//plus d'un jouer ? 													OK
//check carte ferme (flood_fill) donc tu remplace NSEW par 0 
//1. Met ta map dans une struct
//2. pars_map
//	-> check_caractere
//	->trouve joueur
//	-> map ferme ?
//
//secure malloc