/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:15:49 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/05 00:41:05 by felayan          ###   ########.fr       */
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

static void	clean_mlx(mlx_t *mlx, mlx_image_t *img, t_assets *ass)
{
	if (mlx)
	{
		if (img)
			mlx_delete_image(mlx, img);
		if (ass -> no_tex)
			mlx_delete_texture(ass -> no_tex);
		if (ass -> so_tex)
			mlx_delete_texture(ass -> so_tex);
		if (ass -> we_tex)
			mlx_delete_texture(ass -> we_tex);
		if (ass -> ea_tex)
			mlx_delete_texture(ass -> ea_tex);
		mlx_terminate(mlx);
	}
}

void	clean_cub3d(t_cub3d *cub, int err)
{
	free(cub -> config.no_conf);
	free(cub -> config.so_conf);
	free(cub -> config.we_conf);
	free(cub -> config.ea_conf);
	clean_strs(cub -> map.grid);
	clean_strs(cub -> file);
	clean_mlx(cub -> mlx, cub -> img, &cub -> ass);
	if (err != EXIT_SUCCESS)
		print_err_and_exit(err);
	exit(EXIT_SUCCESS);
}
