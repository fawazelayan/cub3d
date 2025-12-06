/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:52:02 by felayan           #+#    #+#             */
/*   Updated: 2025/12/06 14:06:25 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_rgb(int rgb[])
{
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 0xFF);
}

void	calculate_hitpoint(t_ray *ray, t_render *ren, t_player *pl)
{
	if (ray -> side == WE)
		ren -> wall_hitp = pl -> py + ray -> wall_dist * ray -> raydiry;
	else
		ren -> wall_hitp = pl -> px + ray -> wall_dist * ray -> raydirx;
	ren -> wall_hitp -= floor(ren -> wall_hitp);
	ren -> tex_x = ren -> wall_hitp * ren -> tex -> width;
	if (ren -> tex_x >= (int)ren -> tex -> width)
		ren -> tex_x = ren -> tex -> width - 1;
	else if (ren -> tex_x < 0)
		ren -> tex_x = 0;
	if (ray -> side == WE && ray -> raydirx < 0)
		ren -> tex_x = ren -> tex -> width - ren -> tex_x - 1;
	if (ray -> side == NS && ray -> raydiry > 0)
		ren -> tex_x = ren -> tex -> width - ren -> tex_x - 1;
	ren -> scale = 1.0 * ren -> tex -> height / ren -> wall_h;
	ren->tex_pos = (ren->draw_st - HEIGHT / 2 + ren->wall_h / 2) * ren->scale;
}

static uint32_t	get_pixel(mlx_texture_t *tex, int x, int y)
{
	uint32_t	pixel;
	uint8_t		rgba[4];
	int			index;

	index = (y * tex -> width + x) * tex -> bytes_per_pixel;
	rgba[0] = tex -> pixels[index];
	rgba[1] = tex -> pixels[index + 1];
	rgba[2] = tex -> pixels[index + 2];
	rgba[3] = tex -> pixels[index + 3];
	pixel = rgba[0] << 24 | rgba[1] << 16 | rgba[2] << 8 | rgba[3];
	return (pixel);
}

void	draw(t_render *ren, mlx_image_t *img, int x)
{
	int			y;
	int			tex_y;
	uint32_t	pixel;

	y = ren -> draw_st;
	while (y <= ren -> draw_end)
	{
		tex_y = (int)ren -> tex_pos & (ren -> tex -> height - 1);
		ren -> tex_pos += ren -> scale;
		pixel = get_pixel(ren -> tex, ren -> tex_x, tex_y);
		mlx_put_pixel(img, x, y, pixel);
		y++;
	}
}
