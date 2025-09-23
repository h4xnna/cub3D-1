/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/23 21:27:36 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int check_cub(char *str)
{
	int i= 0;
	if(ft_strlen(str) < 5 )
		return(FAILURE);
	while(str[i + 4] )
			i++;	
	if(ft_strncmp(&str[i], ".cub", 4) && str)
		return(FAILURE);
	return(SUCCESS);
}


int checks_args(int ac, char **av)
{
	if(ac != 2)
	{
		error_message("Mauvais nb d'args");
		return(FAILURE);
	}
	if(check_cub(av[1]))
	{
		error_message("Mauvais extension");
		return(FAILURE);
	}
	return (SUCCESS);
}

void free_pars(t_pars *pars)
{
	if(pars->colors)
		free_split(pars->colors, len_tab(pars->colors));
	if(pars->line_split)
		free_split(pars->line_split, len_tab(pars->line_split));
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

int check_map(t_pars *pars, t_map_info *infos)
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
			return (FAILURE);
		i = 0;
		while (i < 3)
		{
			if (ft_atoi(pars->colors[i]) >= 0 && ft_atoi(pars->colors[i]) <= 255 )
			{
				stock_colors( infos, pars, ft_atoi(pars->colors[i]), i);
				i++;
			}
			else 
				return(FAILURE);
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
	t_pars		pars;
	
	ft_bzero(&infos, sizeof(t_map_info));
	ft_bzero(&pars, sizeof(t_pars));

	if(checks_args(ac, av))
		return(FAILURE);
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
			break;
		}
		pars.line_split = ft_split(line, ' ');
		if(check_map(&pars, &infos))
		{
			free(line);
			free_pars(&pars);
			error_message("NTM");
			break;
		}
		// printf("%s\n", line);
		free(line);
		if(pars.line_split)
			free_split(pars.line_split, len_tab(pars.line_split));
		pars.line_split = NULL;
		if(pars.colors)
			free_split(pars.colors, len_tab(pars.colors));
		pars.colors = NULL;
		
	}
	if(infos.count_info != 6 || check_infos(&infos))
		return (FAILURE);
	print_info(infos);
	free_all(&infos);
	// free_pars(&pars);
	close(fd);
	return (SUCCESS);
}
