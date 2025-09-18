/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/18 17:05:13 by hmimouni         ###   ########.fr       */
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
void free_all(t_map_info *info)
{
	if(info->EA)
		free(info->EA);
	if(info->SO)
		free(info->SO);
	if(info->WE)
		free(info->WE);
	if(info->C)
		free(info->C);
	if(info->F)
		free(info->F);
	if(info->NO)
		free(info->NO);
}

int check_map(char **line_split, t_map_info *infos)
{
	char **colors = NULL;
	int i;

	if (!line_split || (len_tab(line_split) != 2 && line_split[0]))
		return (FAILURE);
	if (!line_split[0])
		return (SUCCESS);
	if (!is_direction(line_split[0]) && !is_fichier(line_split[1]))
	{
		fill_struct(infos, line_split[0], line_split[1]);
		infos->count_info += 1; 
		return (SUCCESS);
	}
	else if (!ft_strcmp(line_split[0], "F") || !ft_strcmp(line_split[0], "C"))
	{
		if(allouer_colors(line_split[0], infos))
			return(FAILURE);
		colors = ft_split(line_split[1], ',');
		if (!colors || len_tab(colors) != 3)
			return (FAILURE);
		i = 0;
		while (i < 3)
		{
			if (ft_atoi(colors[i]) >= 0 && ft_atoi(colors[i]) <= 255 )
			{
				stock_colors(infos, line_split[0], ft_atoi(colors[i]), i);
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
	
	ft_bzero(&infos, sizeof(t_map_info));
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
		char **split = ft_split(line, ' ');
		if(check_map(split, &infos))
		{
			free(line);
			free_split(split,len_tab(split));
			error_message("NTM");
			break;
		}
		// printf("%s\n", line);
		free(line);
		free_split(split, len_tab(split));
	}
	if(infos.count_info != 6)
		return (FAILURE);
	if (check_infos(&infos))
		return(FAILURE);
	print_info(infos);
	free_all(&infos);
	close(fd);
	return (SUCCESS);
}
