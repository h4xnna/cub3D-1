/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/26 17:59:18 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	int			fd;
	t_map_info	infos;
	t_info_pars	pars;
	t_map_pars	map;
	t_data		data;
	t_win		*win;

	if (init_structs(&map, &infos, &pars, &fd, &data) || checks_args(ac, av)
		|| check_fd(&fd, av))
		return (FAILURE);
	if (parse_file(fd, &map, &infos, &pars))
	{
		// free_info(&data.map_info);
		return (FAILURE);
	}
	data.map_pars = map;
	data.info_pars = pars;
	data.map_info = infos;
	if (final_checks(&infos, &map))
		return (FAILURE);
	// print_info(infos, map);
	if (flood_fill(&map))
	{
		error_message(" map pas  ferme");
		clean_exit(&data);
		return (FAILURE);
	}
	// print_char(map.map);
	// write(1, "\n", 1);
	// write(1, "\n", 1);
	x_to_0(&map);
	// print_char(map.map);
	data.player.px = map.x_start + 0.5;
	data.player.py = map.y_start + 0.5;
	data.player.pa = PI / 2;
	data.player.pdirx = 0;
	data.player.pdiry = -1;
	data.player.planex = 0.66;
	data.player.planey = 0;
	win = init_win();
	if (!win)
	{
		error_message("Error : initialisation fenêtre");
		return (FAILURE);
	}
	data.win = *win;
	free(win);
	load_all_textures(&data);
	set_player_direction(&data.player, map.position);
	mlx_hook(data.win.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win.win, 17, 0L, (int (*)())clean_exit, &data);
	mlx_loop_hook(data.win.mlx, &render, &data);
	mlx_loop(data.win.mlx);
	free_win(&data.win);
	free_info(&infos);
	free_tab(map.map);
	close(fd);
	return (SUCCESS);
}
