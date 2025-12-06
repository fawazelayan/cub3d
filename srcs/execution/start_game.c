/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 18:34:18 by felayan           #+#    #+#             */
/*   Updated: 2025/12/06 14:05:59 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_game(void *param)
{
	t_cub3d	*cub;

	cub = param;
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_W)
		|| mlx_is_key_down(cub -> mlx, MLX_KEY_UP))
		move_forward(&cub -> pl, cub -> mlx, &cub -> map);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_A))
		move_left(&cub -> pl, cub -> mlx, &cub -> map);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_S)
		|| mlx_is_key_down(cub -> mlx, MLX_KEY_DOWN))
		move_backward(&cub -> pl, cub -> mlx, &cub -> map);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_D))
		move_right(&cub -> pl, cub -> mlx, &cub -> map);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_LEFT))
		rotate_left(&cub -> pl);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_RIGHT))
		rotate_right(&cub -> pl);
	render_floor_ceil(cub -> img, &cub -> ass);
	render_rays(cub);
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
	init_player(&cub -> pl);
	cub -> ass.f_color = get_rgb(cub -> config.f_rgb);
	cub -> ass.c_color = get_rgb(cub -> config.c_rgb);
	hooks_setup(cub);
	mlx_loop(cub -> mlx);
}
