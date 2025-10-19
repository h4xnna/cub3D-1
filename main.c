/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:26:45 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/19 14:11:51 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double rotSpeed = 0.05;

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

// Normalisation d'un vecteur 2D
void normalize_vector(double *x, double *y)
{
    double length = sqrt((*x) * (*x) + (*y) * (*y));
    if (length != 0)
    {
        *x /= length;
        *y /= length;
    }
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
	{
		mlx_destroy_window(data->win.mlx, data->win.win);
		mlx_clear_window(data->win.mlx, data->win.win);
		exit(1);
	}
	if (keycode == 65361) // fleche guache
	{
		double oldDirX = data->player.pdirx;
		data->player.pdirx = data->player.pdirx * cos(-rotSpeed) - data->player.pdiry * sin(-rotSpeed);
		data->player.pdiry = oldDirX * sin(-rotSpeed) + data->player.pdiry * cos(-rotSpeed);
		double oldPlaneX = data->player.planeX;
		data->player.planeX = data->player.planeX * cos(-rotSpeed) - data->player.planeY * sin(-rotSpeed);
		data->player.planeY = oldPlaneX * sin(-rotSpeed) + data->player.planeY * cos(-rotSpeed);
		normalize_vector(&data->player.pdirx, &data->player.pdiry);
		normalize_vector(&data->player.planeX, &data->player.planeY);
		
	}
	
	if (keycode == 65363) // fleche droite
	{
		double oldDirX = data->player.pdirx;
		data->player.pdirx = data->player.pdirx * cos(rotSpeed) - data->player.pdiry * sin(rotSpeed);
		data->player.pdiry = oldDirX * sin(rotSpeed) + data->player.pdiry * cos(rotSpeed);
		double oldPlaneX = data->player.planeX;
		data->player.planeX = data->player.planeX * cos(rotSpeed) - data->player.planeY * sin(rotSpeed);
		data->player.planeY = oldPlaneX * sin(rotSpeed) + data->player.planeY * cos(rotSpeed);
		normalize_vector(&data->player.pdirx, &data->player.pdiry);
		normalize_vector(&data->player.planeX, &data->player.planeY);
		
	}

	return (0);
}
int render(t_data *data)
{
	clear_window(&data->win);
	split_win(data);
	drawRays2D(data);
	(void)data;
	return (0);
}
t_win    *init_win(void)
{
    t_win    *win;

    win = (t_win *)ft_calloc(1, sizeof(t_win));
    if (!win)
        return (NULL);
    win->mlx = NULL;
    win->win = NULL;
    win->img = NULL;
    win->addr = NULL;
    win->bits_per_pixel = 0;
    win->line_length = 0;
    win->endian = 0;
    win->mlx = mlx_init();
    if (!win->mlx)
        return (NULL);
    win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT, "damn");
    if (!win->win)
        return (NULL);
    win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
    if (!win->img)
        return (NULL);
    win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
            &win->line_length, &win->endian);
    mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
    return (win);
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
		error_message("map pas ferme");
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
	data.player.pa = PI / 2;
	data.player.pdirx = 0;
	data.player.pdiry = -1;
	data.player.planeX = 0.66;
	data.player.planeY = 0;
	t_win *win = init_win();
	if (!win)
	{
		error_message("Erreur initialisation fenêtre");
		return (FAILURE);
	}
	data.win = *win; // copie la structure
	free(win);       // libère le pointeur temporaire alloué dans init_win()
	// free_info(&infos);
	// close(fd);
	// free_tab(map.map);
	// data.mlx_ptr = mlx_init();
	// if (!data.mlx_ptr)
	// {
	// 	error_message("MLX: error connecting to mlx.");
	// 	return (1);
	// }
	// data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Gros ZIZI");
	// if (!data.win_ptr)
	// {
	// 	error_message("GROS PIPI");
	// 	return (1);
	// }
	set_player_direction(&data.player, map.position);
	mlx_hook(data.win.win, 2, 1L << 0, key_press, &data);
	mlx_loop_hook(data.win.mlx, &render, &data);
	mlx_loop(data.win.mlx);
	return (SUCCESS);
}
