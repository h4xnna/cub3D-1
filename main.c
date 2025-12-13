/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2025/12/13 11:02:23 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_data(	t_data	*data, t_map_pars *map)
{
	data->player = ft_calloc(1, sizeof(t_player));
	data->raycast = ft_calloc(1, sizeof(t_raycast));
	data->texture = ft_calloc(1, sizeof(t_texture));
	data->player->px = map->x_start + 0.5;
	data->player->py = map->y_start + 0.5;
	data->player->sensitivity = 0.001;
	data->player->delta_time = 0.016;
	data->player->mouse_x = WIDTH / 2;
	data->player->pitch = 0;
	data->player->show_knife = false;
	data->map_pars->height = len_tab(data->map_pars->map);
}

int	main(int ac, char **av)
{
	int			fd;
	t_map_info	*infos;
	t_info_pars	*pars;
	t_map_pars	*map;
	t_data		*data;
	t_win		*win;

	infos = NULL;
	pars = NULL;
	map = NULL;
	data = NULL;
	win = NULL;
	if (init_structs(&map, &infos, &pars, &fd, &data) || checks_args(ac, av)
		|| check_fd(&fd, av))
		return (FAILURE);
	if (parse_file(fd, map, infos, pars))
		return (FAILURE);
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
	init_data(data, map);
	make_doors(data);
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
	mlx_mouse_hide(data->win->mlx, data->win->win);
	mlx_mouse_move(data->win->mlx, data->win->win, WIDTH / 2, HEIGHT / 2);
	mlx_hook(data->win->win, 2, 1L << 0, (int (*)())key_press, data);
	mlx_hook(data->win->win, 3, 1L << 1, (int (*)())key_release, data);
	mlx_hook(data->win->win, 6, 1L << 6, (int (*)())mouse_info, data);
	mlx_mouse_hook(data->win->win, (int (*)())mouse_hook, data);
	mlx_hook(data->win->win, 17, 0L, (int (*)())clean_exit, data);
	mlx_loop_hook(data->win->mlx, (int (*)())render, data);
	mlx_loop(data->win->mlx);
	free_win(data->win);
	free_info(infos);
	free_tab(map->map);
	close(fd);
	return (SUCCESS);
}
