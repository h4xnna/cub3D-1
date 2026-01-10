/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_loading.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:29:05 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/10 15:52:49 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_animation(t_animation *anim, int frame_count, double duration)
{
	anim->frame_count = frame_count;
	anim->current_frame = 0;
	anim->frame_time = duration / frame_count;
	anim->timer = 0.0;
	anim->duration = duration;
	anim->playing = 1;
}

static void	load_anim_textures(t_data *data, t_animation **anim, char *pattern,
		int frame_count)
{
	int		i;
	char	path[128];

	i = 0;
	while (i < frame_count)
	{
		snprintf(path, sizeof(path), pattern, i + 1);
		(*anim)->frames[i] = load_one_texture(data, (*anim)->frames[i], path);
		if (!(*anim)->frames[i])
		{
			while (--i >= 0)
				free_texture((*anim)->frames[i], data->win->mlx);
			free((*anim)->frames);
			free(*anim);
			clean_exit(data);
		}
		i++;
	}
}

static t_animation	*load_animation(t_data *data, char *pattern,
		int frame_count, double duration)
{
	t_animation	*anim;

	anim = malloc(sizeof(t_animation));
	if (!anim)
	{
		error_message("Animation malloc failed");
		clean_exit(data);
	}
	anim->frames = malloc(sizeof(t_img *) * frame_count);
	if (!anim->frames)
	{
		free(anim);
		clean_exit(data);
	}
	init_animation(anim, frame_count, duration);
	load_anim_textures(data, &anim, pattern, frame_count);
	return (anim);
}

void	load_animations(t_data *data)
{
	data->knife_anim = load_animation(data,
			"./assets/textures/anims/inspect/frame_%03d.xpm", 144, 4.78);
	data->deploy_anim = load_animation(data,
			"./assets/textures/anims/deploy/frame_%02d.xpm", 29, 0.96);
	data->lmb_anim = load_animation(data,
			"./assets/textures/anims/left/frame_%02d.xpm", 33, 1.09);
	data->rmb_anim = load_animation(data,
			"./assets/textures/anims/right/frame_%02d.xpm", 30, 1.0);
}
