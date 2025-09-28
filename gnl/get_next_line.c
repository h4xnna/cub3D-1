/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 23:52:35 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/28 14:01:39 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(char *stock_line, int fd)
{
	char	*buffer;
	int		bytesread;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytesread = 1;
	while (bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
			return (free(buffer), free(stock_line), NULL);
		buffer[bytesread] = '\0';
		stock_line = ft_strjoin(stock_line, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stock_line);
}

int	len(char *stock_line)
{
	int	i;

	i = 0;
	if (stock_line)
	{
		while (stock_line[i])
		{
			if (stock_line[i] == '\n')
				return (i + 1);
			i++;
		}
	}
	return (i);
}

char	*extract_line(char *stock_line)
{
	char	*res_line;
	int		i;

	i = 0;
	res_line = NULL;
	if (!stock_line[0])
		return (NULL);
	res_line = malloc(ft_strlen(stock_line) + 1);
	if (!res_line)
		return (NULL);
	while (stock_line[i] && stock_line[i] != '\n')
	{
		res_line[i] = stock_line[i];
		i++;
	}
	if (stock_line[i] == '\n')
		res_line[i++] = '\n';
	res_line[i] = '\0';
	return (res_line);
}

char	*clear_stock(char *stock_line)
{
	char	*new_stock;
	int		i;
	int		total_len;
	int		stock_start;

	new_stock = NULL;
	stock_start = len(stock_line);
	i = 0;
	total_len = ft_strlen(stock_line) - len(stock_line);
	if (!total_len)
		return (free(stock_line), NULL);
	new_stock = malloc(total_len + 1);
	if (!new_stock)
		return (NULL);
	while (stock_line[stock_start] != '\0')
	{
		new_stock[i] = stock_line[stock_start++];
		i++;
	}
	new_stock[i] = '\0';
	free(stock_line);
	return (new_stock);
}

char	*get_next_line(int fd)
{
	static char	*stock_line = NULL;
	char		*line;

	line = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
	{
		if(stock_line)
			free(stock_line), stock_line = NULL;
		return (NULL);
	}
	stock_line = read_line(stock_line, fd);
	if (!stock_line)
		return (NULL);
	line = extract_line(stock_line);
	stock_line = clear_stock(stock_line);
	if (!line)
		return (free(stock_line), NULL);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int i = 0;
// 	int j = 0;
	
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