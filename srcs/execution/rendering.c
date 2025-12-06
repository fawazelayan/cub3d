/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:55:24 by felayan           #+#    #+#             */
/*   Updated: 2025/12/06 14:05:59 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_floor_ceil(mlx_image_t *img, t_assets *ass)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(img, j, i, ass -> c_color);
			j++;
		}
		i++;
	}
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(img, j, i, ass -> f_color);
			j++;
		}
		i++;
	}
}

void	render_rays(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		cub -> ray.cam_x = (2 * i / (double)WIDTH) - 1;
		cub->ray.raydirx = cub->pl.dirx + (cub->pl.planex * cub->ray.cam_x);
		cub->ray.raydiry = cub->pl.diry + (cub->pl.planey * cub->ray.cam_x);
		cub -> ray.mapx = (int)cub -> pl.px;
		cub -> ray.mapy = (int)cub -> pl.py;
		calculate_dist(&cub -> ray, &cub -> pl);
		perform_dda(&cub -> ray, &cub -> map);
		get_texture(&cub -> ray, &cub -> render, &cub -> ass);
		calculate_hitpoint(&cub -> ray, &cub -> render, &cub -> pl);
		draw(&cub -> render, cub -> img, i);
		i++;
	}
}
