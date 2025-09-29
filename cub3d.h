/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:24:03 by hmimouni          #+#    #+#             */
/*   Updated: 2025/09/29 18:16:37 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define FAILURE 1
# define SUCCESS 0

typedef struct s_info_pars
{
	char	**line_split;
	char	**colors;

}			t_info_pars;

typedef struct s_map_pars
{
	char	**map;
	char	position;
	int		close;
	int		x_start;
	int		y_start;
	int		map_started;
}			t_map_pars;

// typedef struct s_map
// {
// 	int x_start;
// 	int y_start;
// }	t_map;

typedef struct s_map_info
{
	char	*south;
	char	*west;
	char	*east;
	char	*north;
	int		*floor;
	int		*ceiling;
	int		count_info;
}			t_map_info;

// utils_pars1
int			len_tab(char **tab);
char		*remove_newline(char *line);
int			ft_strcmp(char *str, char *str2);
int			is_fichier(char *path);
int			is_direction(char *str);

// utils_pars2
void		print_info(t_map_info info, t_map_pars map);
void		fill_struct(t_map_info *infos, char *direction, char *path);
void		stock_colors(t_map_info *infos, t_info_pars *pars, int nb, int i);
int			allouer_colors(t_info_pars *pars, t_map_info *infos);
void		print_char(char **str);

// utils_pars3
void		error_message(char *error);
int			check_infos(t_map_info *info);
int			check_cub(char *str);
int			checks_args(int ac, char **av);
void		*ft_realloc(void *ptr, size_t new_size);

// pars_map
int			check_positions(t_map_pars *map, char *line);
int			add_line_to_map(t_map_pars *map, char *line);
int			check_char(char *line, t_map_pars *map);
int			is_full_of_spaces(char *line);
int			check_fd(int *fd, char **av);

// free_pars1
void		free_info(t_map_info *info);
void		free_tab(char **tab);
void		free_pars(t_info_pars *pars);

// pars_map2
void		print_char(char **str);
int			print_tab(int *tab);
int			skip_space(char *line);
long long	ft_atoll(const char *nptr);

// info_pars4
int			pars_info(t_info_pars *pars, t_map_info *infos);

// struct pars : line split etc..
// struct game : info ...

#endif