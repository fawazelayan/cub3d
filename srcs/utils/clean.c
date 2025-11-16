/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:15:49 by aalquraa          #+#    #+#             */
/*   Updated: 2025/11/17 01:02:02 by felayan          ###   ########.fr       */
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
	if (cub -> file)
		clean_strs(cub -> file);
	if (cub -> config.no_conf)
		free(cub -> config.no_conf);
	if (cub -> config.so_conf)
		free(cub -> config.so_conf);
	if (cub -> config.we_conf)
		free(cub -> config.we_conf);
	if (cub -> config.ea_conf)
		free(cub -> config.ea_conf);
	if (cub -> map.grid)
		clean_strs(cub -> map.grid);
	if (cub->mlx)
	{
		if (cub->img)
			mlx_delete_image(cub->mlx, cub->img);

		if (cub->ass.no_tex)
			mlx_delete_texture(cub->ass.no_tex);
		if (cub->ass.so_tex)
			mlx_delete_texture(cub->ass.so_tex);
		if (cub->ass.we_tex)
			mlx_delete_texture(cub->ass.we_tex);
		if (cub->ass.ea_tex)
			mlx_delete_texture(cub->ass.ea_tex);
		if (cub -> mlx -> window)
			mlx_close_window(cub -> mlx);
		mlx_terminate(cub->mlx);
	}

	if (err != EXIT_SUCCESS)
		print_err_and_exit(err);
	exit(EXIT_SUCCESS);
}
