/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 07:53:02 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/03 17:59:41 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static double	get_time_seconds(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec + t.tv_usec / 1000000.0);
}

t_door	*find_door(t_door *doors, int y, int x)
{
	while (doors)
	{
		if (doors->y == y && doors->x == x)
			return (doors);
		doors = doors->next;
	}
	return (NULL);
}

static void	update_doors(t_data *data, double delta_time)
{
	t_door	*door;

	door = data->doors;
	while (door)
	{
		if (sqrt(pow(data->player->px - (door->x + 0.5), 2)
				+ pow(data->player->py - (door->y + 0.5), 2)) < 1.45)
		{
			if (door->opening >= 0.0 || !door->opened)
				door->opened = 1;
		}
		else
		{
			data->map_pars->map[door->y][door->x] = 'D';
			door->opened = -1;
		}
		if (door->opened == 1 && door->opening < 1.0)
			door->opening += delta_time * 0.8;
		else if (door->opened == -1 && door->opening > 0.0)
			door->opening += delta_time * -0.8;
		if (door->opening >= 1.0)
		{
			door->opening = 1.0;
			data->map_pars->map[door->y][door->x] = '0';
		}
		if (door->opening <= 0.0)
			door->opening = 0.0;
		door = door->next;
	}
}

void	update_animation(t_animation *anim, double delta_time)
{
	if (!anim->playing)
		return ;
	anim->timer += delta_time;
	if (anim->timer >= anim->frame_time)
	{
		anim->timer -= anim->frame_time;
		anim->current_frame++;
		if (anim->current_frame >= anim->frame_count)
		{
			anim->current_frame = 0;
			anim->playing = 0;
		}
	}
}

static unsigned int	make_final_color(unsigned int floor_color,
		unsigned int reflected_color, unsigned int wall_color)
{
	t_color			floort;
	t_color			wall;
	t_color			reflect;
	t_color			final;
	unsigned int	final_color;

	floort.r = (floor_color >> 16) & 0xFF;
	floort.g = (floor_color >> 8) & 0xFF;
	floort.b = floor_color & 0xFF;
	reflect.r = (reflected_color >> 16) & 0xFF;
	reflect.g = (reflected_color >> 8) & 0xFF;
	reflect.b = reflected_color & 0xFF;
	wall.r = (wall_color >> 16) & 0xFF;
	wall.g = (wall_color >> 8) & 0xFF;
	wall.b = wall_color & 0xFF;
	final.r = (uint8_t)((floort.r * (1.0 - REFLECTIONSTRENGTH * 3) + reflect.r
				* REFLECTIONSTRENGTH + wall.r * REFLECTIONSTRENGTH * 2));
	final.g = (uint8_t)((floort.g * (1.0 - REFLECTIONSTRENGTH * 3) + reflect.g
				* REFLECTIONSTRENGTH + wall.g * REFLECTIONSTRENGTH * 2));
	final.b = (uint8_t)((floort.b * (1.0 - REFLECTIONSTRENGTH * 3) + reflect.b
				* REFLECTIONSTRENGTH + wall.b * REFLECTIONSTRENGTH * 2));
	final_color = (final.r << 16) | (final.g << 8) | final.b;
	return (final_color);
}

static void	init_step_side_dist(t_data *data)
{
	if (data->raycast->raydirx < 0)
	{
		data->raycast->stepx = -1;
		data->raycast->sidedistx = (data->player->px - data->raycast->mapx)
			* data->raycast->delta_dist_x;
	}
	else
	{
		data->raycast->stepx = 1;
		data->raycast->sidedistx = (data->raycast->mapx + 1.0
				- data->player->px) * data->raycast->delta_dist_x;
	}
	if (data->raycast->raydiry < 0)
	{
		data->raycast->stepy = -1;
		data->raycast->side_dist_y = (data->player->py - data->raycast->mapy)
			* data->raycast->delta_dist_y;
	}
	else
	{
		data->raycast->stepy = 1;
		data->raycast->side_dist_y = (data->raycast->mapy + 1.0
				- data->player->py) * data->raycast->delta_dist_y;
	}
}

static void	init_raycasting(t_data *data, int x)
{
	data->raycast->camerax = 2 * x / (double)WIDTH - 1;
	// calcul dir rayon chaque colonne
	data->raycast->raydirx = data->player->pdirx + data->player->planex
		* data->raycast->camerax;
	data->raycast->raydiry = data->player->pdiry + data->player->planey
		* data->raycast->camerax;
	if (data->raycast->raydirx == 0)
		data->raycast->raydirx = 0.001;
	if (data->raycast->raydiry == 0)
		data->raycast->raydiry = 0.001;
	data->raycast->mapx = (int)data->player->px;
	// convert pos joeurs coordonne case map
	data->raycast->mapy = (int)data->player->py;
	data->raycast->delta_dist_x = fabs(1 / data->raycast->raydirx);
	// distance rayon parcourus jusqua ligne map
	data->raycast->delta_dist_y = fabs(1 / data->raycast->raydiry);
	// fabs = valeur positivie
	init_step_side_dist(data);
}

static void	draw_wall(t_data *data, int x, double wall_x)
{
	int				tex_x;
	int				tex_y;
	int				y;
	int				d;
	unsigned int	color;

	tex_x = (int)(wall_x * (double)data->raycast->texture->width);
	if ((data->raycast->side == 0 && data->raycast->raydirx > 0)
		|| (data->raycast->side == 1 && data->raycast->raydiry < 0))
		tex_x = data->raycast->texture->width - tex_x - 1;
	y = data->raycast->draw_start;
	while (y <= data->raycast->draw_end)
	{
		d = y * 256 - HEIGHT * 128 + data->raycast->line_height * 128;
		tex_y = ((d * data->raycast->texture->height)
				/ data->raycast->line_height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		color = ((int *)data->raycast->texture->addr)[data->raycast->texture->height
			* tex_y + tex_x];
		color = apply_shading(data->raycast->perpwall_dist / 2, color);
		my_mlx_pixel_put(data->win, x, y, color);
		if ((y + (data->raycast->draw_end - y) * 2) < HEIGHT)
		{
			my_mlx_pixel_put(data->win, x, y + (data->raycast->draw_end - y)
				* 2, color);
		}
		y++;
	}
}

static void	choose_texture(t_data *data)
{
	if (data->raycast->side == 0)
	{
		if (data->raycast->raydirx > 0)
			data->raycast->texture = data->texture->text_west;
		else
			data->raycast->texture = data->texture->text_east;
	}
	else
	{
		if (data->raycast->raydiry > 0)
			data->raycast->texture = data->texture->text_north;
		else
			data->raycast->texture = data->texture->text_south;
	}
}

static void	init_drawing(t_data *data)
{
	if (data->raycast->side == 0)
		data->raycast->perpwall_dist = data->raycast->sidedistx
			- data->raycast->delta_dist_x;
	else
		data->raycast->perpwall_dist = data->raycast->side_dist_y
			- data->raycast->delta_dist_y; // fish eyes fix
	data->raycast->line_height = (int)(HEIGHT / data->raycast->perpwall_dist);
	data->raycast->draw_start = -data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_start < 0)
		data->raycast->draw_start = 0;
	data->raycast->draw_end = data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_end >= HEIGHT)
		data->raycast->draw_end = HEIGHT - 1;
}

static void	get_wall_x(t_data *data, double *wall_x)
{
	t_door	*door;

	if (data->raycast->side == 0)
		*wall_x = data->player->py + data->raycast->perpwall_dist
			* data->raycast->raydiry;
	else
		*wall_x = data->player->px + data->raycast->perpwall_dist
			* data->raycast->raydirx;
	*wall_x -= floor(*wall_x);
	if (data->map_pars->map[data->raycast->mapy][data->raycast->mapx] == 'D'
		&& data->raycast->skip == false)
	{
		door = find_door(data->doors, data->raycast->mapy, data->raycast->mapx);
		*wall_x -= door->opening;
		if (*wall_x <= 0.0)
		{
			data->raycast->skip = true;
			data->raycast->hit = 0;
		}
	}
}

static void	step_through(t_data *data)
{
	if (data->raycast->sidedistx < data->raycast->side_dist_y)
	{
		data->raycast->sidedistx += data->raycast->delta_dist_x;
		data->raycast->mapx += data->raycast->stepx;
		data->raycast->side = 0;
	}
	else
	{
		data->raycast->side_dist_y += data->raycast->delta_dist_y;
		data->raycast->mapy += data->raycast->stepy;
		data->raycast->side = 1;
	}
}

static void	perform_dda(t_data *data, double *wall_x)
{
	data->raycast->skip = false;
	data->raycast->hit = 0;
	while (data->raycast->hit == 0)
	{
		step_through(data);
		if (data->map_pars->map[data->raycast->mapy]
			&& (data->map_pars->map[data->raycast->mapy][data->raycast->mapx] == '1'
				|| (data->map_pars->map[data->raycast->mapy][data->raycast->mapx] == 'D'
					&& data->raycast->skip == false)))
			data->raycast->hit = 1;
		else
			continue ;
		init_drawing(data);
		choose_texture(data);
		get_wall_x(data, wall_x);
		data->raycast->skip = false;
	}
}

static void	compute_floor_wall_coords(t_data *data, double wall_x,
		t_point *floor_coords)
{
	if (data->raycast->side == 0 && data->raycast->raydirx > 0)
	{
		floor_coords->x = data->raycast->mapx;
		floor_coords->y = data->raycast->mapy + wall_x;
	}
	else if (data->raycast->side == 0 && data->raycast->raydirx < 0)
	{
		floor_coords->x = data->raycast->mapx + 1.0;
		floor_coords->y = data->raycast->mapy + wall_x;
	}
	else if (data->raycast->side == 1 && data->raycast->raydiry > 0)
	{
		floor_coords->x = data->raycast->mapx + wall_x;
		floor_coords->y = data->raycast->mapy;
	}
	else
	{
		floor_coords->x = data->raycast->mapx + wall_x;
		floor_coords->y = data->raycast->mapy + 1.0;
	}
}

static void	compute_floor_coords(t_data *data, int p, t_point floor_coords,
		t_point *current_floor_coords)
{
	double	weight;

	weight = (HEIGHT / (2.0 * p - HEIGHT)) / data->raycast->perpwall_dist;
	current_floor_coords->x = weight * floor_coords.x + (1.0 - weight)
		* data->player->px;
	current_floor_coords->y = weight * floor_coords.y + (1.0 - weight)
		* data->player->py;
}

static int	sample_floor_color(t_data *data, t_point f_coords, int *is_floor)
{
	t_img	*ftex;
	int		ftex_x;
	int		ftex_y;
	int		floor_color;
	t_color	exit_color;

	if ((f_coords.y > 0 && f_coords.y < data->map_pars->height)
		&& data->map_pars->map[(int)f_coords.y][(int)f_coords.x] == 'L')
	{
		ftex = data->texture->exit;
		ftex_x = (int)(f_coords.x * ftex->width) % ftex->width;
		ftex_y = (int)(f_coords.y * ftex->height) % ftex->height;
		floor_color = ((int *)ftex->addr)[ftex->width * ftex_y + ftex_x];
		exit_color.g = (floor_color >> 8) & 0xFF;
		if (exit_color.g > 0)
			ftex = data->texture->floor;
	}
	else
		ftex = data->texture->floor;
	ftex_x = (int)(f_coords.x * ftex->width) % ftex->width;
	ftex_y = (int)(f_coords.y * ftex->height) % ftex->height;
	floor_color = ((int *)ftex->addr)[ftex->width * ftex_y + ftex_x];
	*is_floor = (ftex == data->texture->floor);
	return (floor_color);
}

static void	render_floor_pixel(t_data *data, int x, int p, t_point floor_coords)
{
	t_point	current_floor_coords;
	int		floor_color;
	int		is_floor;
	int		reflected_color;
	int		wall_color;

	compute_floor_coords(data, p, floor_coords, &current_floor_coords);
	floor_color = sample_floor_color(data, current_floor_coords, &is_floor);
	reflected_color = 0;
	wall_color = 0;
	if (is_floor)
	{
		reflected_color = get_window_pixel(data->win, x, HEIGHT - p);
		wall_color = get_window_pixel(data->win, x, p);
	}
	my_mlx_pixel_put(data->win, x, p, apply_shading((HEIGHT / (2.0 * p
					- HEIGHT)) / 2, make_final_color(floor_color,
				reflected_color, wall_color)));
}

static void	drawRays2D(t_data *data)
{
	int		x;
	int		p;
	double	wall_x;
	t_point	floor_coords;

	x = 0;
	while (x < WIDTH)
	{
		init_raycasting(data, x);
		perform_dda(data, &wall_x);
		draw_wall(data, x, wall_x);
		compute_floor_wall_coords(data, wall_x, &floor_coords);
		p = data->raycast->draw_end;
		while (p < HEIGHT)
		{
			render_floor_pixel(data, x, p, floor_coords);
			p++;
		}
		x++;
	}
}

static void	update_animations(t_data *data)
{
	update_animation(data->knife_anim, data->player->delta_time);
	update_animation(data->deploy_anim, data->player->delta_time);
	update_animation(data->lmb_anim, data->player->delta_time);
	update_animation(data->rmb_anim, data->player->delta_time);
}

static t_animation	*switch_anim(t_data *data)
{
	if (data->deploy_anim->playing || data->knife_anim->playing
		|| data->lmb_anim->playing || data->rmb_anim->playing)
	{
		if (data->deploy_anim->playing)
			return (data->deploy_anim);
		if (data->knife_anim->playing)
			return (data->knife_anim);
		if (data->lmb_anim->playing)
			return (data->lmb_anim);
		if (data->rmb_anim->playing)
			return (data->rmb_anim);
	}
	else
		draw_image_to_buffer(data->win,
			data->deploy_anim->frames[data->deploy_anim->frame_count - 1],
			0, 0);
}

static void	display_overlay(t_data *data)
{
	t_animation *anim;

	if (data->player->show_knife)
	{
		if (data->deploy_anim->playing || data->knife_anim->playing
			|| data->lmb_anim->playing || data->rmb_anim->playing)
		{
			anim = switch_anim(data);
			if (data->deploy_anim->playing)
				draw_image_to_buffer(data->win,
					data->deploy_anim->frames[data->deploy_anim->current_frame],
					0, 0);
			if (data->knife_anim->playing)
				draw_image_to_buffer(data->win,
					data->knife_anim->frames[data->knife_anim->current_frame],
					0, 0);
			if (data->lmb_anim->playing)
				draw_image_to_buffer(data->win,
					data->lmb_anim->frames[data->lmb_anim->current_frame], 0,
					0);
			if (data->rmb_anim->playing)
				draw_image_to_buffer(data->win,
					data->rmb_anim->frames[data->rmb_anim->current_frame], 0,
					0);
		}
		else
			draw_image_to_buffer(data->win,
				data->deploy_anim->frames[data->deploy_anim->frame_count - 1],
				0, 0);
	}
}

int	render(t_data *data)
{
	static double last_time = 0;
	double current_time = get_time_seconds();
	data->player->delta_time = current_time - last_time;
	if (data->player->delta_time >= 1)
		data->player->delta_time = 0.016;
	last_time = current_time;

	double fps = 1.0 / data->player->delta_time;

	clear_window(data->win);

	draw_skybox(data);
	drawRays2D(data);
	draw_map(data);
	player_position(data);
	rotate_player(data, data->player->mouse_x);
	update_doors(data, data->player->delta_time);
	update_animations(data);
	display_overlay(data);

	mlx_put_image_to_window(data->win->mlx, data->win->win, data->win->img, 0,
		0);
	mlx_string_put(data->win->mlx, data->win->win, WIDTH - 20, 20, 0xFFFFFF,
		ft_itoa((int)fps));

	return (0);
}