/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2025/12/16 17:26:30 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	int			fd;
	t_data		*data = NULL;
	t_win		*win = NULL;

	if (init_structs(&data) || checks_args(ac, av)
		|| check_fd(&fd, av) || parse_file(fd, data->map_pars, data->map_info, data->info_pars)
		|| final_checks(data->map_info, data->map_pars))
	{	
		clean_exit(data);
		return (FAILURE);
	}

	if (flood_fill(data->map_pars))
	{
		error_message("map pas ferme");
		clean_exit(data);
		return (FAILURE);
	}

	data->player = ft_calloc(1, sizeof(t_player));
	data->raycast = ft_calloc(1, sizeof(t_raycast));
	data->texture = ft_calloc(1, sizeof(t_texture));
	data->player->px = data->map_pars->x_start + 0.5;
	data->player->py = data->map_pars->y_start + 0.5;
	data->map_pars->height = len_tab(data->map_pars->map);


	win = init_win();
	if (!win)
	{
		error_message("Error : initialisation fenêtre");
		return (FAILURE);
	}
	data->win = win;
	load_all_textures(data);
	set_player_direction(data->player, data->map_pars->position);
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
	free_info(data->map_info);
	free_tab(data->map_pars->map);
	close(fd);
	return (SUCCESS);
}
