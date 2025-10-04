/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:43:22 by hmimouni          #+#    #+#             */
/*   Updated: 2025/10/04 18:22:54 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "cub3d.h"

 void buttons_a( t_player *player)
 {
	player->pa -= 0.001; 
	if(player->pa < 0)
		player->pa +=  2*PI;
	player->pdx = cos(player->pa) * 5;
	player->pdy = sin(player->pa) * 5;
 }
  void buttons_d( t_player *player)
 {
	player->pa -= 0.001; 
	if(player->pa < 0)
		player->pa +=  2*PI;
	player->pdx = cos(player->pa) * 5;
	player->pdy = sin(player->pa) * 5;
 }

 