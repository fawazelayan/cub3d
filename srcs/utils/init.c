/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:16:10 by aalquraa          #+#    #+#             */
/*   Updated: 2025/11/17 00:47:09 by felayan          ###   ########.fr       */
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

