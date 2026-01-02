/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2026/01/02 18:31:57 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	final_initializations(t_data *data)
{
	data->player->px = data->map_pars->x_start + 0.5;
	data->player->py = data->map_pars->y_start + 0.5;
	data->player->sensitivity = 0.001;
	data->player->delta_time = 0.016;
	data->player->mouse_x = WIDTH / 2;
	data->player->pitch = 0;
	data->player->show_knife = false;
	data->map_pars->height = len_tab(data->map_pars->map);
	load_all_textures(data);
	make_doors(data);
	set_player_direction(data->player, data->map_pars->position);
	normalize_vector(&data->player->pdirx, &data->player->pdiry);
	normalize_vector(&data->player->planex, &data->player->planey);
}

int	initialize_everything(t_data **data, int ac, char **av)
{
	int	fd;

	if (checks_args(ac, av) == FAILURE || check_fd(&fd, av) == FAILURE)
		return (FAILURE);
	if (init_data(data, fd) == FAILURE)
	{
		error_message("Structs initialization failed");
		return (free_data(*data), FAILURE);
	}
	if (parse_file(fd, (*data)->map_pars, (*data)->map_info, (*data)->info_pars)
		|| final_checks((*data)->map_info, (*data)->map_pars))
		return (free_data(*data), FAILURE);
	if (flood_fill((*data)->map_pars))
	{
		error_message("Map is not closed");
		return (free_data(*data), FAILURE);
	}
	final_initializations((*data));
	return (SUCCESS);
}

int	init_data(t_data **data, int fd)
{
	(*data) = ft_calloc(1, sizeof(t_data));
	if (!*data)
		return (close(fd), FAILURE);
	(*data)->fd = fd;
	(*data)->map_pars = ft_calloc(1, sizeof(t_map_pars));
	(*data)->map_info = ft_calloc(1, sizeof(t_map_info));
	(*data)->info_pars = ft_calloc(1, sizeof(t_info_pars));
	if (!(*data)->map_pars || !(*data)->map_info || !(*data)->info_pars)
		return (FAILURE);
	(*data)->map_pars->map = ft_calloc(1, sizeof(char *));
	if (!(*data)->map_pars->map)
		return (FAILURE);
	(*data)->player = ft_calloc(1, sizeof(t_player));
	(*data)->raycast = ft_calloc(1, sizeof(t_raycast));
	(*data)->texture = ft_calloc(1, sizeof(t_texture));
	if (!(*data)->player || !(*data)->raycast || !(*data)->texture)
		return (FAILURE);
	(*data)->win = init_win();
	if (!(*data)->win)
		return (FAILURE);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (initialize_everything(&data, ac, av) == FAILURE)
		return (FAILURE);
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
	free_data(data);
	return (SUCCESS);
}
