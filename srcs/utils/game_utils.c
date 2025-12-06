/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:27:30 by felayan           #+#    #+#             */
/*   Updated: 2025/12/06 14:39:36 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_delta_dist(t_ray *ray)
{
	if (!ray -> raydirx)
		ray -> dlta_distx = 1e30;
	else
		ray -> dlta_distx = fabs(1.0 / ray -> raydirx);
	if (!ray -> raydiry)
		ray -> dlta_disty = 1e30;
	else
		ray -> dlta_disty = fabs(1.0 / ray -> raydiry);
}

void	calculate_dist(t_ray *ray, t_player *pl)
{
	calc_delta_dist(ray);
	if (ray -> raydirx < 0)
	{
		ray -> stepx = -1;
		ray -> side_distx = (pl -> px - ray -> mapx) * ray -> dlta_distx;
	}
	else
	{
		ray -> stepx = 1;
		ray -> side_distx = (ray -> mapx + 1 - pl -> px) * ray -> dlta_distx;
	}
	if (ray -> raydiry < 0)
	{
		ray -> stepy = -1;
		ray -> side_disty = (pl -> py - ray -> mapy) * ray -> dlta_disty;
	}
	else
	{
		ray -> stepy = 1;
		ray -> side_disty = (ray -> mapy + 1 - pl -> py) * ray -> dlta_disty;
	}
}

void	perform_dda(t_ray *ray, t_map *map)
{
	ray -> hit = false;
	while (!ray -> hit)
	{
		if (ray -> side_distx < ray -> side_disty)
		{
			ray -> side_distx += ray -> dlta_distx;
			ray -> mapx += ray -> stepx;
			ray -> side = WE;
		}
		else
		{
			ray -> side_disty += ray -> dlta_disty;
			ray -> mapy += ray -> stepy;
			ray -> side = NS;
		}
		if (map -> grid[ray -> mapy][ray -> mapx] == '1')
			ray -> hit = true;
	}
	if (ray -> side == WE)
		ray -> wall_dist = ray -> side_distx - ray -> dlta_distx;
	else
		ray -> wall_dist = ray -> side_disty - ray -> dlta_disty;
	if (ray -> wall_dist < 0.001)
		ray -> wall_dist = 0.001;
}

void	get_texture(t_ray *ray, t_render *ren, t_assets *ass)
{
	ren -> wall_h = (int)(HEIGHT / ray -> wall_dist);
	ren -> draw_st = HEIGHT / 2 - ren -> wall_h / 2;
	if (ren -> draw_st < 0)
		ren -> draw_st = 0;
	ren -> draw_end = HEIGHT / 2 + ren -> wall_h / 2;
	if (ren -> draw_end >= HEIGHT)
		ren -> draw_end = HEIGHT - 1;
	if (ray -> side == WE)
	{
		if (ray -> raydirx < 0)
			ren -> tex = ass -> ea_tex;
		else
			ren -> tex = ass -> we_tex;
	}
	else
	{
		if (ray -> raydiry < 0)
			ren -> tex = ass -> so_tex;
		else
			ren -> tex = ass -> no_tex;
	}
}
