/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:42:07 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/06 14:46:26 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	char	**config;
	char	**map;
	t_cub3d	cub3d;

	validate_program(ac, av[1]);
	init_cub3d(&cub3d);
	parse_file(&cub3d, av[1]);
	split_file(&cub3d, &config, &map);
	if (!parse_config_file(&cub3d, config)
		|| !validate_config(&cub3d.config) || !parse_map(&cub3d, map))
	{
		clean_strs(config);
		clean_strs(map);
		clean_cub3d(&cub3d, ERR_CONFIG);
	}
	clean_strs(config);
	clean_strs(map);
	start_game(&cub3d);
}
