/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 04:51:48 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/05 04:58:30 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_char(char m)
{
	if (m == '0' || m == '1' || m == 'N' || m == 'S' || m == 'E' || m == 'W'
		|| m == ' ')
		return (1);
	return (0);
}

int	is_player_char(char p)
{
	if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
		return (1);
	return (0);
}

int	max_width(char **map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

void	free_partial(char **rect, int i)
{
	while (--i >= 0)
		free(rect[i]);
	free(rect);
}

void	fill_row(char *dst, char *src, int width)
{
	int	j;
	int	len;

	j = -1;
	len = ft_strlen(src);
	while (++j < len)
		dst[j] = src[j];
	while (j < width)
		dst[j++] = ' ';
	dst[width] = '\0';
}
