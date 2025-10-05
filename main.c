/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/05 16:59:03 by hmimouni         ###   ########.fr       */
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

int	init_structs(t_map_pars *map, t_map_info *infos, t_info_pars *pars, int *fd,
		t_data *data)
{
	*fd = 0;
	ft_bzero(map, sizeof(t_map_pars));
	ft_bzero(infos, sizeof(t_map_info));
	ft_bzero(pars, sizeof(t_info_pars));
	ft_bzero(data, sizeof(t_data));
	map->map = malloc(sizeof(char *) * 1);
	if (!map->map)
		return (1);
	map->map[0] = NULL;
	return (0);
}

int render(t_data *data)
{
	(void)data;
	return (0);
}
int	key_press(int keycode, t_data *data)
{
	if (keycode == A_KEY)
		buttons_a(&data->player, &data->map_pars);
	if (keycode == D_KEY)
		buttons_d(&data->player, &data->map_pars);
	if(keycode == S_KEY)
		buttons_s(&data->player, &data->map_pars);
	if(keycode == W_KEY)
		buttons_w(&data->player, &data->map_pars);
	if (keycode == 65307)
		exit(1);
	draw_map(data);
	draw_square(data, (data->player.px * SIZE_SQUARE + 10),(data->player.py * SIZE_SQUARE + 10), 0xFF00FF00, SIZE_SQUARE/ 3);
	return (0);
}

int	main(int ac, char **av)
{
	int			fd;
	t_map_info	infos;
	t_info_pars	pars;
	t_map_pars	map;
	t_data		data;

	if (init_structs(&map, &infos, &pars, &fd, &data) || checks_args(ac, av)
		|| check_fd(&fd, av))
		return (FAILURE);
	if (parse_file(fd, &map, &infos, &pars))
		return (FAILURE);
	if (final_checks(&infos, &map))
		return (FAILURE);
	// print_info(infos, map);
	if (flood_fill(&map))
	{
		error_message("Gros caca");
		return (FAILURE);
	}
	print_char(map.map);
	write(1, "\n", 1);
	write(1, "\n", 1);
	x_to_0(&map);
	print_char(map.map);
	data.map_pars = map;
	data.info_pars = pars;
	data.map_info = infos;
	data.player.px = map.x_start;
	data.player.py = map.y_start;
	// free_info(&infos);
	// close(fd);
	// free_tab(map.map);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	{
		error_message("MLX: error connecting to mlx.");
		return (1);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Gros ZIZI");
	if (!data.win_ptr)
	{
		error_message("GROS PIPI");
		return (1);
	}
	draw_map(&data);
	draw_square(&data, (data.map_pars.x_start * SIZE_SQUARE + 10),(data.map_pars.y_start * SIZE_SQUARE + 10), 0xFF00FF00, SIZE_SQUARE/ 3);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_press, &data);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_loop(data.mlx_ptr);
	return (SUCCESS);
}
