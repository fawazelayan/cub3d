/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 18:34:18 by felayan           #+#    #+#             */
/*   Updated: 2025/12/05 02:06:07 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_game(void *param)
{
	t_cub3d	*cub;

	cub = param;
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_W)
		|| mlx_is_key_down(cub -> mlx, MLX_KEY_UP))
		move_forward(&cub -> player, cub -> mlx, &cub -> map);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_A))
		move_left(&cub -> player, cub -> mlx, &cub -> map);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_S)
		|| mlx_is_key_down(cub -> mlx, MLX_KEY_DOWN))
		move_backward(&cub -> player, cub -> mlx, &cub -> map);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_D))
		move_right(&cub -> player, cub -> mlx, &cub -> map);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_LEFT))
		rotate_left(&cub -> player);
	if (mlx_is_key_down(cub -> mlx, MLX_KEY_RIGHT))
		rotate_right(&cub -> player);
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
	init_player(&cub -> player);
	cub -> ass.f_color = get_rgb(cub -> config.f_rgb);
	cub -> ass.c_color = get_rgb(cub -> config.c_rgb);
	hooks_setup(cub);
	mlx_loop(cub -> mlx);
}
