/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2025/11/06 11:33:04 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	int			fd;
	t_map_info	*infos = NULL;
	t_info_pars	*pars = NULL;
	t_map_pars	*map = NULL;
	t_data		*data = NULL;
	t_win		*win = NULL;

	if (init_structs(&map, &infos, &pars, &fd, &data) || checks_args(ac, av)
		|| check_fd(&fd, av))
		return (FAILURE);
	if (parse_file(fd, map, infos, pars))
	{
		// free_info(data->map_info);
		return (FAILURE);
	}
	data->map_pars = map;
	data->info_pars = pars;
	data->map_info = infos;
	if (final_checks(infos, map))
		return (FAILURE);

	if (flood_fill(map))
	{
		error_message("map pas ferme");
		clean_exit(data);
		return (FAILURE);
	}

	data->player = ft_calloc(1, sizeof(t_player));
	data->raycast = ft_calloc(1, sizeof(t_raycast));
	data->texture = ft_calloc(1, sizeof(t_texture));
	data->player->px = map->x_start + 0.5;
	data->player->py = map->y_start + 0.5;
	data->map_pars->height = len_tab(data->map_pars->map);


	win = init_win();
	if (!win)
	{
		error_message("Error : initialisation fenêtre");
		return (FAILURE);
	}
	data->win = win;
	load_all_textures(data);
	set_player_direction(data->player, map->position);
	normalize_vector(&data->player->pdirx, &data->player->pdiry);
	normalize_vector(&data->player->planex, &data->player->planey);
	print_char(data->map_pars->map);
	data->raycast->ceiling = rgb_to_hex_int(data, data->map_info->ceiling);
	data->raycast->floor = rgb_to_hex_int(data, data->map_info->floor);
	mlx_hook(data->win->win, 2, 1L << 0, (int (*)())key_press, data);
	mlx_hook(data->win->win, 17, 0L, (int (*)())clean_exit, data);
	mlx_loop_hook(data->win->mlx, (int (*)())render, data);
	mlx_loop(data->win->mlx);
	free_win(data->win);
	free_info(infos);
	free_tab(map->map);
	close(fd);
	return (SUCCESS);
}
