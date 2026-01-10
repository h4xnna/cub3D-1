/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 11:56:14 by pacda-si          #+#    #+#             */
/*   Updated: 2026/01/08 19:58:25 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	reset_all_animations(t_data *data)
{
	if (data->knife_anim->playing)
	{
		data->knife_anim->playing = 0;
		data->knife_anim->current_frame = 0;
	}
	if (data->deploy_anim->playing)
	{
		data->deploy_anim->playing = 0;
		data->deploy_anim->current_frame = 0;
	}
	if (data->lmb_anim->playing)
	{
		data->lmb_anim->playing = 0;
		data->lmb_anim->current_frame = 0;
	}
	if (data->rmb_anim->playing)
	{
		data->rmb_anim->playing = 0;
		data->rmb_anim->current_frame = 0;
	}
}

static void	update_animation(t_animation *anim, double delta_time)
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

void	update_animations(t_data *data)
{
	update_animation(data->knife_anim, data->player->delta_time);
	update_animation(data->deploy_anim, data->player->delta_time);
	update_animation(data->lmb_anim, data->player->delta_time);
	update_animation(data->rmb_anim, data->player->delta_time);
}

static t_animation	*switch_anim(t_data *data)
{
	if (data->deploy_anim->playing)
		return (data->deploy_anim);
	if (data->knife_anim->playing)
		return (data->knife_anim);
	if (data->lmb_anim->playing)
		return (data->lmb_anim);
	if (data->rmb_anim->playing)
		return (data->rmb_anim);
	return (data->deploy_anim);
}

void	display_overlay(t_data *data)
{
	t_animation	*anim;

	if (data->player->show_knife)
	{
		if (data->deploy_anim->playing || data->knife_anim->playing
			|| data->lmb_anim->playing || data->rmb_anim->playing)
		{
			anim = switch_anim(data);
			draw_image_to_buffer(data->win, anim->frames[anim->current_frame],
				0, 0);
		}
		else
			draw_image_to_buffer(data->win,
				data->deploy_anim->frames[data->deploy_anim->frame_count - 1],
				0, 0);
	}
}
