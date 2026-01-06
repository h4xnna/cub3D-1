/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:19:57 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/06 11:12:40 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_splif(char **out, int i)
{
	while (i > 0)
	{
		free(out[i]);
		i--;
	}
	free(out);
}

void	free_texture(t_img *texture, void *mlx)
{
	if (texture)
	{
		if (texture->img)
			mlx_destroy_image(mlx, texture->img);
		free(texture);
	}
}

void	free_textures(t_data *data)
{
	if (data->texture)
	{
		if (data->texture->text_east)
			free_texture(data->texture->text_east, data->win->mlx);
		if (data->texture->text_north)
			free_texture(data->texture->text_north, data->win->mlx);
		if (data->texture->text_south)
			free_texture(data->texture->text_south, data->win->mlx);
		if (data->texture->text_west)
			free_texture(data->texture->text_west, data->win->mlx);
		if (data->texture->door)
			free_texture(data->texture->door, data->win->mlx);
		if (data->texture->exit)
			free_texture(data->texture->exit, data->win->mlx);
		if (data->texture->floor)
			free_texture(data->texture->floor, data->win->mlx);
		if (data->texture->skybox)
			free_texture(data->texture->skybox, data->win->mlx);
		free(data->texture);
	}
}

static void	free_frames(t_animation *anim, void *mlx)
{
	int		i;
	t_img	**frames;

	frames = anim->frames;
	if (!frames)
		return ;
	i = 0;
	while (i < anim->frame_count)
	{
		if (frames[i]->img)
			mlx_destroy_image(mlx, frames[i]->img);
		free(frames[i]);
		i++;
	}
	free(frames);
}

void	free_animations(t_data *data)
{
	if (data->knife_anim)
	{
		free_frames(data->knife_anim, data->win->mlx);
		free(data->knife_anim);
	}
	if (data->deploy_anim)
	{
		free_frames(data->deploy_anim, data->win->mlx);
		free(data->deploy_anim);
	}
	if (data->lmb_anim)
	{
		free_frames(data->lmb_anim, data->win->mlx);
		free(data->lmb_anim);
	}
	if (data->rmb_anim)
	{
		free_frames(data->rmb_anim, data->win->mlx);
		free(data->rmb_anim);
	}
}

void	free_doors(t_data *data)
{
	t_door	*current;
	t_door	*next;

	current = data->doors;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

static void	free_part2(t_data *data)
{
	if (data->raycast)
		free(data->raycast);
	if (data->texture)
		free_textures(data);
	free_animations(data);
	free_doors(data);
	if (data->win)
		free_win(data->win);
	if (data->fd >= 0)
		close(data->fd);
	if (data->fps)
		free(data->fps);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->map_pars)
	{
		free_tab(data->map_pars->map);
		free(data->map_pars);
	}
	if (data->map_info)
		free_info(data->map_info);
	if (data->info_pars)
	{
		free_pars(data->info_pars);
		free(data->info_pars);
	}
	if (data->player)
		free(data->player);
	free_part2(data);
	free(data);
}

void	clean_exit(t_data *data)
{
	free_data(data);
	exit(0);
}
