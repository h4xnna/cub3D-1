/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/28 18:56:31 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int pars_info(t_info_pars *pars, t_map_info *infos)
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
				free_tab(pars->colors);
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
				free_tab(pars->colors);
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
	int			fd = 0;
	char		*line;
	int 		error = 0;
	t_map_info	infos;
	t_info_pars		pars;
	t_map_pars		map;
	
	ft_bzero(&map, sizeof(t_map_pars));
	ft_bzero(&infos, sizeof(t_map_info));
	ft_bzero(&pars, sizeof(t_info_pars));

	map.map = malloc(sizeof(char*) * 1);
	map.map[0] = NULL;

	if(checks_args(ac, av))
	{
		free_info(&infos);
		free_pars(&pars);
		return(FAILURE);
	}
	check_fd(&fd, av);
	while ((line = get_next_line(fd)) != NULL)
	{
		line = remove_newline(line);
		if(!line)
		{
			error_message("pas line");
			error = 1;
			break;
		}
		if(infos.count_info < 6)
		{
			pars.line_split = ft_split(line, ' ');
			if (!pars.line_split)
			{
				error_message("Erreur split");
				error = 1;
				break;
			}
			if(pars_info(&pars, &infos))
			{
				error_message("check_map pas bon");
				error = 1;
				break;
			}
		}
		else if ((!line[0] || !is_full_of_spaces(line)) && !map.map_started)
		{

		}
		else if(!check_char(line, &map) && !check_positions(&map, line))
			add_line_to_map(&map,line);
		else
		{
			free_tab(map.map);
			free(line);
			free_pars(&pars);
			free_info(&infos);
			get_next_line(-1);
			error_message("TMP");
			return(FAILURE);
		}
		// printf("%s\n", line);
		free(line);
		free_pars(&pars);
	}
	if(error == 1)
	{
		free(line);
		free_pars(&pars);
	}
	print_info(infos, map);
	if (map.position == 0)
	{
		error_message("map invalide: aucune position trouve pour le joeur ");
		free_info(&infos);
		return (FAILURE);
	}
	if(infos.count_info != 6 || check_infos(&infos))
	{
		error_message("Infos pas bon");
		free_info(&infos);
		free_pars(&pars);
		return (FAILURE);
	}
	free_info(&infos);
	// free_pars(&pars);
	close(fd);
	return (SUCCESS);
}

//2. pars_map
//	-> map ferme ?
//secure malloc
