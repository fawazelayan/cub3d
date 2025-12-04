/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 03:47:14 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/04 19:54:53 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy(char **src, int start, int end)
{
	char	**dest;
	int		i;
	int		len;

	len = end - start;
	dest = malloc(sizeof(char *) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (start < end)
	{
		dest[i] = ft_strdup(src[start]);
		if (!dest[i])
		{
			clean_strs(dest);
			return (NULL);
		}
		trim_newline(dest[i]);
		i++;
		start++;
	}
	dest[i] = NULL;
	return (dest);
}

void	split_file(t_cub3d *cub, char ***config, char ***map)
{
	int	map_start;
	int	total;

	map_start = find_map_start(cub->file);
	if (map_start == -1)
		clean_cub3d(cub, ERR_MAP);
	total = count_lines(cub->file);
	*config = copy(cub->file, 0, map_start);
	if (!*config)
		clean_cub3d(cub, ERR_SYS);
	*map = copy(cub->file, map_start, total);
	if (!*map)
	{
		clean_strs(*config);
		clean_cub3d(cub, ERR_SYS);
	}
}
