/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/29 18:25:22 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	final_checks(t_map_info *infos, t_map_pars *map)
{
	if (map->position == 0)
	{
		error_message("map invalide: aucune position trouvée pour le joueur");
		free_info(infos);
		free_tab(map->map);
		return (1);
	}
	if (infos->count_info != 6 || check_infos(infos))
	{
		error_message("Infos pas bon");
		free_info(infos);
		return (1);
	}
	return (0);
}

int	parse_info_line(char *line, t_info_pars *pars, t_map_info *infos)
{
	pars->line_split = ft_split(line, ' ');
	if (!pars->line_split)
		return (1);
	if (pars_info(pars, infos))
		return (1);
	return (0);
}

int	parse_error(t_map_pars *map, t_map_info *infos, t_info_pars *pars,
		char *msg)
{
	error_message(msg);
	if (map->map)
		free_tab(map->map);
	if (pars)
		free_pars(pars);
	if (infos)
		free_info(infos);
	get_next_line(-1);
	return (1);
}

int	parse_file(int fd, t_map_pars *map, t_map_info *infos, t_info_pars *pars)
{
	char	*line;
	int		error;

	error = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		line = remove_newline(line);
		if (!line)
			return (parse_error(map, infos, pars, "Erreur lecture ligne"));
		if (infos->count_info < 6)
		{
			if (parse_info_line(line, pars, infos))
				return (free(line), parse_error(map, infos, pars,
						"Erreur parsing infos"));
		}
		else if ((!line[0] || !is_full_of_spaces(line)) && !map->map_started)
			;
		else if (!check_char(line, map) && !check_positions(map, line))
			add_line_to_map(map, line);
		else
			return (free(line), parse_error(map, infos, pars,
					"Erreur parsing map"));
		free(line);
		free_pars(pars);
	}
	return (0);
}

int	init_structs(t_map_pars *map, t_map_info *infos, t_info_pars *pars, int *fd)
{
	*fd = 0;
	ft_bzero(map, sizeof(t_map_pars));
	ft_bzero(infos, sizeof(t_map_info));
	ft_bzero(pars, sizeof(t_info_pars));
	map->map = malloc(sizeof(char *) * 1);
	if (!map->map)
		return (1);
	map->map[0] = NULL;
	return (0);
}

int	main(int ac, char **av)
{
	int			fd;
	t_map_info	infos;
	t_info_pars	pars;
	t_map_pars	map;
	int			error;

	if (init_structs(&map, &infos, &pars, &fd) || checks_args(ac, av)
		|| check_fd(&fd, av))
		return (FAILURE);
	error = parse_file(fd, &map, &infos, &pars);
	if (error)
		return (FAILURE);
	if (final_checks(&infos, &map))
		return (FAILURE);
	print_info(infos, map);
	free_info(&infos);
	close(fd);
	free_tab(map.map);
	return (SUCCESS);
}

// int	main(int ac, char **av)
// {
// 	int			fd = 0;
// 	char		*line;
// 	int 		error = 0;
// 	t_map_info	infos;
// 	t_info_pars		pars;
// 	t_map_pars		map;

// 	ft_bzero(&map, sizeof(t_map_pars));
// 	ft_bzero(&infos, sizeof(t_map_info));
// 	ft_bzero(&pars, sizeof(t_info_pars));

// 	map.map = malloc(sizeof(char*) * 1);
// 	map.map[0] = NULL;

// 	if(checks_args(ac, av))
// 	{
// 		free_info(&infos);
// 		free_pars(&pars);
// 		return(FAILURE);
// 	}
// 	check_fd(&fd, av);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		line = remove_newline(line);
// 		if(!line)
// 		{
// 			error_message("pas line");
// 			error = 1;
// 			break ;
// 		}
// 		if(infos.count_info < 6)
// 		{
// 			pars.line_split = ft_split(line, ' ');
// 			if (!pars.line_split)
// 			{
// 				error_message("Erreur split");
// 				error = 1;
// 				break ;
// 			}
// 			if(pars_info(&pars, &infos))
// 			{
// 				error_message("check_map pas bon");
// 				error = 1;
// 				break ;
// 			}
// 		}
// 		else if ((!line[0] || !is_full_of_spaces(line)) && !map.map_started)
// 		{

// 		}
// 		else if(!check_char(line, &map) && !check_positions(&map, line))
// 			add_line_to_map(&map,line);
// 		else
// 		{
// 			free_tab(map.map);
// 			free(line);
// 			free_pars(&pars);
// 			free_info(&infos);
// 			get_next_line(-1);
// 			error_message("TMP");
// 			return(FAILURE);
// 		}
// 		// printf("%s\n", line);
// 		free(line);
// 		free_pars(&pars);
// 	}
// 	if(error == 1)
// 	{
// 		free(line);
// 		free_pars(&pars);
// 	}
// 	print_info(infos, map);
// 	if (map.position == 0)
// 	{
// 		error_message("map invalide: aucune position trouve pour le joeur ");
// 		free_info(&infos);
// 		return (FAILURE);
// 	}
// 	if(infos.count_info != 6 || check_infos(&infos))
// 	{
// 		error_message("Infos pas bon");
// 		free_info(&infos);
// 		free_pars(&pars);
// 		return (FAILURE);
// 	}
// 	free_info(&infos);
// 	// free_pars(&pars);
// 	close(fd);
// 	return (SUCCESS);
// }

// //2. pars_map
// //	-> map ferme ?
// //secure malloc
