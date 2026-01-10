/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:20:54 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/08 19:21:57 by pacda-si         ###   ########.fr       */
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