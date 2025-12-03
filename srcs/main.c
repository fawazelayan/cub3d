/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:42:07 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/03 18:03:08 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	printf_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	char	**config;
	char	**map;
	t_cub3d	cub3d;

	validate_program(ac, av[1]);
	init_cub3d(&cub3d);
	parse_file(&cub3d, av[1]);
	split_file(&cub3d, &config, &map);
	if (!parse_config_file(&cub3d, config) || !validate_config(&cub3d.config))
	{
		clean_strs(config);
		clean_strs(map);
		clean_cub3d(&cub3d, ERR_CONFIG);
	}
	if (!parse_map(&cub3d, map))
	{
		clean_strs(config);
		clean_strs(map);
		clean_cub3d(&cub3d, ERR_MAP);
	}
	start_game(&cub3d);
	clean_strs(config);
	clean_strs(map);
	clean_cub3d(&cub3d, EXIT_SUCCESS);
	return (0);
}
