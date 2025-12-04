/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:16:10 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/05 02:06:17 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub3d(t_cub3d *cub)
{
	int	i;

	i = 0;
	ft_bzero(cub, sizeof(t_cub3d));
	while (i < 3)
	{
		cub -> config.f_rgb[i] = -1;
		cub -> config.c_rgb[i] = -1;
		i++;
	}
	cub -> player.px = -1;
	cub -> player.py = -1;
}

void	init_mlx(t_cub3d *cub)
{
	cub -> mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "IDK GAME", false);
	if (!cub -> mlx)
		clean_cub3d(cub, ERR_MLX);
	cub -> img = mlx_new_image(cub -> mlx, WIN_WIDTH, WIN_HEIGHT);
	cub -> ass.no_tex = mlx_load_png(cub -> config.no_conf);
	cub -> ass.so_tex = mlx_load_png(cub -> config.so_conf);
	cub -> ass.we_tex = mlx_load_png(cub -> config.we_conf);
	cub -> ass.ea_tex = mlx_load_png(cub -> config.ea_conf);
	if (!cub -> img || !cub -> ass.no_tex || !cub -> ass.so_tex
		|| !cub -> ass.ea_tex || !cub -> ass.we_tex)
		clean_cub3d(cub, ERR_MLX);
	if (mlx_image_to_window(cub -> mlx, cub -> img, 0, 0) < 0)
		clean_cub3d(cub, ERR_MLX);
}

void	init_player(t_player *pl)
{
	if (pl -> dir == 'N')
	{
		pl -> dirx = 0;
		pl -> diry = -1;
	}
	else if (pl -> dir == 'S')
	{
		pl -> dirx = 0;
		pl -> diry = 1;
	}
	else if (pl -> dir == 'W')
	{
		pl -> dirx = -1;
		pl -> diry = 0;
	}
	else if (pl -> dir == 'E')
	{
		pl -> dirx = 1;
		pl -> diry = 0;
	}
	pl -> planex = -pl -> diry * FOV;
	pl -> planey = pl -> dirx * FOV;
}
