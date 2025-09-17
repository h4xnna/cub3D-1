/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/17 14:43:36 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void error_message(char *error)
{
	write(2, "Error : ", 8);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

// int check_cub(char *str)
// {
// 	int i = 0;
// 	if (ft_strlen(str) < 5)
// 		return (FAILURE);
// 	while(str[i])
// 		i++;
// 	if(str[i- 4] == '.' )
// 	{
// 		if(str[i - 3] == 'c')
// 			if(str[i - 2] == 'u')
// 				if(str[i - 1 == 'b'])
// 					return(SUCCESS);
// 	}
// 	return(FAILURE);
// }

int check_cub(char *str)
{
	int i= 0;
	if(ft_strlen(str) < 5)
		return(FAILURE);
	while(str[i + 4] )
			i++;	
	if(ft_strncmp(&str[i], ".cub", 4))
		return(FAILURE);
	return(SUCCESS);
}


int checks_args(int ac, char **av)
{
	if(ac > 2 || ac < 2)
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
int is_direction(char *str)
{
	if (!ft_strcmp(str, "NO") || !ft_strcmp(str, "EA") ||
		!ft_strcmp(str, "SO") || !ft_strcmp(str, "WE"))
		return (SUCCESS);
	return (FAILURE);
}

int check_map(char *line)
{
	char **str2 = NULL;
	char **str3 = NULL;
	int i;

	if (line)
	{
		str2 = ft_split(line, ' ');
		if (!str2 || len_tab(str2) != 2)
			return ( FAILURE); 
		if (is_direction(str2[0]))
		{
			if (str2[1][0] == '.' && str2[1][1] == '/')
				return ( SUCCESS);
			return (FAILURE);
		}
		else if (!ft_strcmp(str2[0], "F") || !ft_strcmp(str2[0], "C"))
		{
			str3 = ft_split(str2[1], ',');
			if (!str3 || len_tab(str3) != 3)
				return (FAILURE);
			i = 0;
			while (i < 3)
			{
				if (ft_atoi(str3[i]) < 0 || ft_atoi(str3[i]) > 255)
					return (FAILURE);
				i++;
			}
			return (SUCCESS);
		}
		
	}
	
	return ( FAILURE);
}


int	main(int ac, char **av)
{
	int		fd;
	char	*line;

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
		if(check_map(line))
		{
			error_message("NTM");
			break;
		}
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (SUCCESS);
}

// int	main(int ac, char **av)
// {
// 	int		fd;
// 	char	*line;
// 	int i = 0;
// 	int j = 0;
	
	
// 	if(!checks_args(ac))
// 		return(0);
// 	fd = open("cub", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Erreur");
// 		return (0);
// 	}
// 	while ((line = get_next_line(fd)) != NULL )
// 	{
// 		if(line[j] != '1')
// 		{
// 			printf("%s", line);
// 			i++;
// 			free(line);
// 		}
// 		else 
// 			break;
// 		j++;
			
// 	}
// 	if( i > 6)
// 		printf("prout");
// 	close(fd);
// 	return (0);

// }
