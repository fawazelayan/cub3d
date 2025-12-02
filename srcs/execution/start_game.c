/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 18:34:18 by felayan           #+#    #+#             */
/*   Updated: 2025/11/30 00:34:17 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ADD ERRORS LATER TO PRINT_ERROR_AND_EXIT
// HANDLE ERRORS IN CLEAN_CUB3D LATER
static void	init_mlx(t_cub3d *cub)
{
	cub -> mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "IDK GAME", false);
	if (!cub -> mlx)
		clean_cub3d(cub, ERR_MLX_INIT);
	cub -> img = mlx_new_image(cub -> mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub -> img)
		clean_cub3d(cub, ERR_MAIN_IMG_CRT);
	mlx_image_to_window(cub -> mlx, cub -> img, 0, 0);
	cub -> ass.no_tex = mlx_load_png(cub -> config.no_conf);
	if (!cub -> ass.no_tex)
		clean_cub3d(cub, ERR_NO_TEXTURE_LD);
	cub -> ass.so_tex = mlx_load_png(cub -> config.so_conf);
	if (!cub -> ass.so_tex)
		clean_cub3d(cub, ERR_SO_TEXTURE_LD);
	cub -> ass.we_tex = mlx_load_png(cub -> config.we_conf);
	if (!cub -> ass.we_tex)
		clean_cub3d(cub, ERR_WE_TEXTURE_LD);
	cub -> ass.ea_tex = mlx_load_png(cub -> config.ea_conf);
	if (!cub -> ass.ea_tex)
		clean_cub3d(cub, ERR_EA_TEXTURE_LD);
}

static void	init_player(t_player *pl)
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
	pl -> plane_x = -pl -> diry * FOV;
	pl -> plane_y = pl -> dirx * FOV;
}

static void	end_game(void *param)
{
	t_cub3d *cub = param;
	clean_cub3d(cub, EXIT_SUCCESS);
}

void	update_game(void *param)
{
	t_cub3d	*cub = param;

	if (mlx_is_key_down(cub -> mlx, MLX_KEY_W) || mlx_is_key_down(cub -> mlx, MLX_KEY_UP))
		move_forward(cub);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_A))
		move_left(cub);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_S) || mlx_is_key_down(cub -> mlx, MLX_KEY_DOWN))
		move_backward(cub);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_D))
		move_right(cub);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_LEFT))
		rotate_left(cub);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_RIGHT))
		rotate_right(cub);
	render_floor_ceil(cub);
	render_rays(cub);
}

void	esc_press(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub = param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_cub3d(cub, EXIT_SUCCESS);
}
static void	hooks_setup(t_cub3d *cub)
{
	mlx_close_hook(cub -> mlx, end_game, cub);
	mlx_key_hook(cub -> mlx, esc_press, cub);
	mlx_loop_hook(cub -> mlx, update_game, cub);
}

void	start_game(t_cub3d *cub)
{
	init_mlx(cub);
	init_player(&cub -> player);
	cub -> ass.f_color = (cub->config.f_rgb[0] << 24 | cub->config.f_rgb[1] << 16 | cub->config.f_rgb[2] << 8 | 255);
	cub -> ass.c_color = (cub->config.c_rgb[0] << 24 | cub->config.c_rgb[1] << 16 | cub->config.c_rgb[2] << 8 | 255);
	hooks_setup(cub);
	mlx_loop(cub -> mlx);
}
