/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:45:17 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/15 16:57:30 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

int		len(char *stock_line);
char	*extract_line(char *stock_line);
char	*clear_stock(char *stock_line);
char	*get_next_line(int fd);

#endif