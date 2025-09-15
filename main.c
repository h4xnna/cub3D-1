/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/15 17:23:40 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// char *last_word(char **str)
// {
// 	char *str2;
// 	int j = 0;
// 	int i = 0;
// 	while (str[1][i])
// 		i++;
// 	i--;
// 	while (str[1][i] > 32)
// 		i--;
// 	i++;
// 	while (str[1][i])
// 	{
// 		str2[j] = str[1][i];
// 		i++;
// 		j++;
// 	}
// 	printf("%d\n", j);
// 	return(str2);
// }
void error_message(char *error)
{
	write(2, "Error : ", 8);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

int check_cub(char *str)
{
	int i = 0;
	if (ft_strlen(str) < 5)
		return (FAILURE);
	while(str[i])
		i++;
	if(str[i- 4] == '.' )
	{
		if(str[i - 3] == 'c')
			if(str[i - 2] == 'u')
				if(str[i - 1 == 'b'])
					return(SUCCESS);
	}
	return(FAILURE);
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
