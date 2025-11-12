/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:15:49 by aalquraa          #+#    #+#             */
/*   Updated: 2025/11/06 17:55:01 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	clean_cub3d(t_cub3d *cub, int err)
{
	if (cub && cub->file)
		clean_strs(cub->file);
	if (cub)
	{
		if (cub->config.no_conf)
			free(cub->config.no_conf);
		if (cub->config.so_conf)
			free(cub->config.so_conf);
		if (cub->config.we_conf)
			free(cub->config.we_conf);
		if (cub->config.ea_conf)
			free(cub->config.ea_conf);
		if (cub->map.grid)
			clean_strs(cub->map.grid);
	}
	if (err != EXIT_SUCCESS)
		print_err_and_exit(err);
	exit(EXIT_SUCCESS);
}
