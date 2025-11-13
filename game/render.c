/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 07:53:02 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/13 09:32:42 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static double get_time_seconds(void)
{
    struct timeval t;
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

static void	update_doors(t_data	*data, double delta_time)
{
	t_door	*door;

	door = data->doors;
	while (door)
	{
		if (sqrt(pow(data->player->px - (door->x + 0.5), 2) + pow(data->player->py - (door->y + 0.5), 2)) < 1.45)
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
		return;
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

static void drawRays2D(t_data *data)
{
	int x = 0;
	int y = 0;
	int color;
	int d;
	int texY;
	int texX;
    int p;
	double wallX;
    double currentDist;
    double weight;
    static int half_height = HEIGHT / 2;

    double currentFloorX;
    double currentFloorY;

    int floorTexX;
    int floorTexY;

    int floorColor;

    int reflectedY;
    int reflectedColor;
    int wallColor;
    int finalColor;

    double floorXWall, floorYWall;
    bool skip = false;

	t_img *texture;
    t_img *floorTexture;
    t_door  *door;
    t_color floort, wall, reflect, final, exitColor;
	
    while (x < WIDTH)
    {
        data->raycast->camerax = 2 * x / (double)WIDTH - 1; //calcul dir rayon chaque colonne
        data->raycast->raydirx = data->player->pdirx + data->player->planex * data->raycast->camerax;
        data->raycast->raydiry = data->player->pdiry + data->player->planey * data->raycast->camerax;

        if (data->raycast->raydirx == 0)
            data->raycast->raydirx = 0.001;
        if (data->raycast->raydiry == 0)
            data->raycast->raydiry = 0.001;

        data->raycast->mapx = (int)data->player->px;
        data->raycast->mapy = (int)data->player->py;

        data->raycast->delta_dist_x = fabs(1 / data->raycast->raydirx); // distance rayon parcourus jusqua ligne map
        data->raycast->delta_dist_y = fabs(1 / data->raycast->raydiry);// fabs = valeur positivie 

        if (data->raycast->raydirx < 0)
        {
            data->raycast->stepx = -1;
            data->raycast->sidedistx = (data->player->px - data->raycast->mapx) * data->raycast->delta_dist_x;
        }
        else
        {
            data->raycast->stepx = 1;
            data->raycast->sidedistx = (data->raycast->mapx + 1.0 - data->player->px) * data->raycast->delta_dist_x;
        }

        if (data->raycast->raydiry < 0) // algo DDA pour avacer rayon de la map
        {
            data->raycast->stepy = -1;
            data->raycast->side_dist_y = (data->player->py - data->raycast->mapy) * data->raycast->delta_dist_y;
        }
        else
        {
            data->raycast->stepy = 1;
            data->raycast->side_dist_y = (data->raycast->mapy + 1.0 - data->player->py) * data->raycast->delta_dist_y;
        }

        data->raycast->hit = 0;
        while (data->raycast->hit == 0) //0 = vertical
        {
            if (data->raycast->sidedistx < data->raycast->side_dist_y) // si rayon a frapper un mur vertical ou horizontal
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

            if (data->map_pars->map[data->raycast->mapy] &&
                (data->map_pars->map[data->raycast->mapy][data->raycast->mapx] == '1' || (data->map_pars->map[data->raycast->mapy][data->raycast->mapx] == 'D' && skip == false))) // si mur stop DDA
                data->raycast->hit = 1;
            else
                continue;

            if (data->raycast->side == 0)
                data->raycast->perpwall_dist = data->raycast->sidedistx - data->raycast->delta_dist_x;
            else
                data->raycast->perpwall_dist = data->raycast->side_dist_y - data->raycast->delta_dist_y; // fish eyes fix

            data->raycast->line_height = (int)(HEIGHT / data->raycast->perpwall_dist);
            data->raycast->draw_start = -data->raycast->line_height / 2 + half_height + data->player->pitch;
            if (data->raycast->draw_start < 0) data->raycast->draw_start = 0;
            data->raycast->draw_end = data->raycast->line_height / 2 + half_height + data->player->pitch;
            if (data->raycast->draw_end >= HEIGHT) data->raycast->draw_end = HEIGHT - 1; //  calcul hauteur de la colonne a dessiner a lecran 

            if (data->raycast->side == 0)
            {
                if (data->raycast->raydirx > 0)
                    texture = data->texture->text_West;
                else
                    texture = data->texture->text_East;
            }
            else
            {
                if (data->raycast->raydiry > 0)
                    texture = data->texture->text_North;
                else
                    texture = data->texture->text_South;
            }

            if (data->raycast->side == 0)
                wallX = data->player->py + data->raycast->perpwall_dist * data->raycast->raydiry;
            else
                wallX = data->player->px + data->raycast->perpwall_dist * data->raycast->raydirx;
            wallX -= floor(wallX);

            if (data->map_pars->map[data->raycast->mapy][data->raycast->mapx] == 'D' && !skip)
            {
                door = find_door(data->doors, data->raycast->mapy, data->raycast->mapx);
                wallX -= door->opening;
                if (wallX <= 0.0)
                {
                    skip = true;
                    data->raycast->hit = 0;
                    continue ;
                }
            }
            skip = false;
            break;
        }
		// draw_line( data);

    	texX = (int)(wallX * (double)texture->width);
        if ((data->raycast->side == 0 && data->raycast->raydirx > 0) ||
            (data->raycast->side == 1 && data->raycast->raydiry < 0))
            texX = texture->width - texX - 1;

		y = data->raycast->draw_start;
        while (y <= data->raycast->draw_end)
        {
			d = (y - data->player->pitch) * 256 - HEIGHT * 128 + data->raycast->line_height * 128;
			texY = ((d * texture->height) / data->raycast->line_height) / 256;
			if (texY < 0)
				texY = 0;

            color = ((int *)texture->addr)[texture->height * texY + texX];
            color = apply_shading(data->raycast->perpwall_dist / 2, color);
            my_mlx_pixel_put(data->win, x, y, color);
            if (data->player->pitch > -800 && (y + (data->raycast->draw_end - y) * 2) < HEIGHT)
            {
                my_mlx_pixel_put(data->win, x, y + (data->raycast->draw_end - y) * 2, color);
            }
			y++;
        }

        if (data->player->pitch > -500)
        {
            
            if (data->raycast->side == 0 && data->raycast->raydirx > 0)
            {
                floorXWall = data->raycast->mapx;
                floorYWall = data->raycast->mapy + wallX;
            }
            else if (data->raycast->side == 0 && data->raycast->raydirx < 0)
            {
                floorXWall = data->raycast->mapx + 1.0;
                floorYWall = data->raycast->mapy + wallX;
            }
            else if (data->raycast->side == 1 && data->raycast->raydiry > 0)
            {
                floorXWall = data->raycast->mapx + wallX;
                floorYWall = data->raycast->mapy;
            }
            else
            {
                floorXWall = data->raycast->mapx + wallX;
                floorYWall = data->raycast->mapy + 1.0;
            }
    
            p = data->raycast->draw_end;
            while (p < HEIGHT)
            {
                currentDist = HEIGHT / (2.0 * p - HEIGHT);
                weight = currentDist / data->raycast->perpwall_dist;
    
                
                currentFloorX = weight * floorXWall + (1.0 - weight) * data->player->px;
                currentFloorY = weight * floorYWall + (1.0 - weight) * data->player->py;
                if ((currentFloorY > 0 && currentFloorY < data->map_pars->height) && data->map_pars->map[(int)currentFloorY][(int)currentFloorX] == 'L')
                {
                    floorTexture = data->texture->exit;
                    floorTexX = (int)(currentFloorX * floorTexture->width) % floorTexture->width;
                    floorTexY = (int)(currentFloorY * floorTexture->height) % floorTexture->height;
        
                    floorColor = ((int *)floorTexture->addr)[floorTexture->width * floorTexY + floorTexX];
    
                    exitColor.g = (floorColor >> 8) & 0xFF;
                    if (exitColor.g > 0)
                    {
                        floorTexture = data->texture->floor;
                    }
                }
                else
                    floorTexture = data->texture->floor;
                
                floorTexX = (int)(currentFloorX * floorTexture->width) % floorTexture->width;
                floorTexY = (int)(currentFloorY * floorTexture->height) % floorTexture->height;
    
                floorColor = ((int *)floorTexture->addr)[floorTexture->width * floorTexY + floorTexX];
    
                
    
                reflectedY = HEIGHT - p;
                if (floorTexture == data->texture->floor)
                {
                    reflectedColor = get_window_pixel(data->win, x, reflectedY);
                    wallColor = get_window_pixel(data->win, x, p);
                }
                else
                {
                    reflectedColor = 0;
                    wallColor = 0;
                }
    
                floort.r = (floorColor >> 16) & 0xFF;
                floort.g = (floorColor >> 8) & 0xFF;
                floort.b = floorColor & 0xFF;

                reflect.r = (reflectedColor >> 16) & 0xFF;
                reflect.g = (reflectedColor >> 8) & 0xFF;
                reflect.b = reflectedColor & 0xFF;
    
                wall.r = (wallColor >> 16) & 0xFF;
                wall.g = (wallColor >> 8) & 0xFF;
                wall.b = wallColor & 0xFF;
    
                final.r = (uint8_t)((floort.r * (1.0 - REFLECTIONSTRENGTH * 3) + reflect.r * REFLECTIONSTRENGTH + wall.r * REFLECTIONSTRENGTH * 2));
                final.g = (uint8_t)((floort.g * (1.0 - REFLECTIONSTRENGTH * 3) + reflect.g * REFLECTIONSTRENGTH + wall.g * REFLECTIONSTRENGTH * 2));
                final.b = (uint8_t)((floort.b * (1.0 - REFLECTIONSTRENGTH * 3) + reflect.b * REFLECTIONSTRENGTH + wall.b * REFLECTIONSTRENGTH * 2));
    
                finalColor = (final.r << 16) | (final.g << 8) | final.b;
                my_mlx_pixel_put(data->win, x, p, apply_shading(currentDist / 2, finalColor));
    
                p++;
            }
        }
        x++;
    }
}


int render(t_data *data)
{
	static double last_time = 0;
    double current_time = get_time_seconds();
	data->player->delta_time = current_time - last_time;
	if (data->player->delta_time >= 1)
		data->player->delta_time = 0.016;
	last_time = current_time;
	
	double fps = 1.0 / data->player->delta_time;
	
    clear_window(data->win);

	if (!data->player->pitch)
	{
		drawSkybox(data);
	}
	drawRays2D(data);
	draw_map(data);
	player_position(data);
	rotate_player(data, data->player->mouse_x);
	update_doors(data, data->player->delta_time);
	update_animation(data->knife_anim, data->player->delta_time);

	if (!data->player->pitch && data->player->show_knife)
	{
		if (data->knife_anim->playing)
			draw_image_to_buffer(data->win, data->knife_anim->frames[data->knife_anim->current_frame], 0, 0);
		else
			draw_image_to_buffer(data->win, data->knife_anim->frames[data->knife_anim->frame_count - 1], 0, 0);
	}

	mlx_put_image_to_window(data->win->mlx, data->win->win, data->win->img, 0, 0);
	mlx_string_put(data->win->mlx, data->win->win, WIDTH - 20, 20, 0xFFFFFF, ft_itoa((int)fps));

    return (0);
}