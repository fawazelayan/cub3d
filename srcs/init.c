/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 04:49:03 by aalquraa          #+#    #+#             */
/*   Updated: 2025/10/20 00:01:12 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init(t_cub3d *cub3d)
{
    cub3d->config.no = NULL;
    cub3d->config.so = NULL;
    cub3d->config.we = NULL;
    cub3d->config.ea = NULL;
    cub3d->config.floor.r = -1;
    cub3d->config.floor.g = -1;
    cub3d->config.floor.b = -1;
    cub3d->config.ceiling.r = -1;
    cub3d->config.ceiling.g = -1;
    cub3d->config.ceiling.b = -1;
    
    cub3d->map.game_map = NULL;
    cub3d->map.width = 0;
    cub3d->map.height = 0;
    cub3d->map.player_x = -1;
    cub3d->map.player_y = -1;
    cub3d->map.player_dir = '\0';
}