/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_and_close.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 00:40:12 by felayan           #+#    #+#             */
/*   Updated: 2025/12/05 00:49:44 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_player *pl)
{
	double	old_dirx;

	old_dirx = pl -> dirx;
	pl -> dirx = old_dirx * cos(ROT_SPEED) - pl -> diry * sin(ROT_SPEED);
	pl -> diry = old_dirx * sin(ROT_SPEED) + pl -> diry * cos(ROT_SPEED);
	pl -> planex = -pl -> diry * FOV;
	pl -> planey = pl -> dirx * FOV;
}

void	rotate_left(t_player *pl)
{
	double	old_dirx;

	old_dirx = pl -> dirx;
	pl -> dirx = old_dirx * cos(ROT_SPEED) + pl -> diry * sin(ROT_SPEED);
	pl -> diry = -old_dirx * sin(ROT_SPEED) + pl -> diry * cos(ROT_SPEED);
	pl -> planex = -pl -> diry * FOV;
	pl -> planey = pl -> dirx * FOV;
}

void	esc_press(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub;

	cub = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_cub3d(cub, EXIT_SUCCESS);
}

void	end_game(void *param)
{
	t_cub3d	*cub;

	cub = param;
	clean_cub3d(cub, EXIT_SUCCESS);
}
