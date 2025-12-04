/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 00:44:08 by felayan           #+#    #+#             */
/*   Updated: 2025/12/05 02:26:00 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_player *pl, mlx_t *mlx, t_map *map)
{
	double	new_px;
	double	new_py;

	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		pl -> move_speed = SPRINT_SPEED;
	else
		pl -> move_speed = MOVE_SPEED;
	new_px = pl -> px + pl -> dirx * pl -> move_speed;
	new_py = pl -> py + pl -> diry * pl -> move_speed;
	if (map -> grid[(int)(pl -> py)][(int)(new_px)] != '1')
		pl -> px = new_px;
	if (map -> grid[(int)(new_py)][(int)(pl -> px)] != '1')
		pl -> py = new_py;
}

void	move_backward(t_player *pl, mlx_t *mlx, t_map *map)
{
	double	new_px;
	double	new_py;

	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		pl -> move_speed = SPRINT_SPEED;
	else
		pl -> move_speed = MOVE_SPEED;
	new_px = pl -> px - pl -> dirx * pl -> move_speed;
	new_py = pl -> py - pl -> diry * pl -> move_speed;
	if (map -> grid[(int)(pl -> py)][(int)(new_px)] != '1')
		pl -> px = new_px;
	if (map -> grid[(int)(new_py)][(int)(pl -> px)] != '1')
		pl -> py = new_py;
}

void	move_right(t_player *pl, mlx_t *mlx, t_map *map)
{
	double	new_px;
	double	new_py;

	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		pl -> move_speed = SPRINT_SPEED;
	else
		pl -> move_speed = MOVE_SPEED;
	new_px = pl -> px - pl -> diry * pl -> move_speed;
	new_py = pl -> py + pl -> dirx * pl -> move_speed;
	if (map -> grid[(int)(pl -> py)][(int)(new_px)] != '1')
		pl -> px = new_px;
	if (map -> grid[(int)(new_py)][(int)(pl -> px)] != '1')
		pl -> py = new_py;
}

void	move_left(t_player *pl, mlx_t *mlx, t_map *map)
{
	double	new_px;
	double	new_py;

	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		pl -> move_speed = SPRINT_SPEED;
	else
		pl -> move_speed = MOVE_SPEED;
	new_px = pl -> px + pl -> diry * pl -> move_speed;
	new_py = pl -> py - pl -> dirx * pl -> move_speed;
	if (map -> grid[(int)(pl -> py)][(int)(new_px)] != '1')
		pl -> px = new_px;
	if (map -> grid[(int)(new_py)][(int)(pl -> px)] != '1')
		pl -> py = new_py;
}
