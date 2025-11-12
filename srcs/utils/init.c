/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:16:10 by aalquraa          #+#    #+#             */
/*   Updated: 2025/11/06 17:54:30 by aalquraa         ###   ########.fr       */
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

