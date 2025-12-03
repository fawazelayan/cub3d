/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:05:16 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/03 19:38:09 by aalquraa         ###   ########.fr       */
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
	int j = -1;
	int len = ft_strlen(src);

	while (++j < len)
		dst[j] = src[j];
	while (j < width)
		dst[j++] = ' ';
	dst[width] = '\0';
}

char	**make_rectangle(char **map, int width, int height)
{
	char	**rect;
	int		i;

	rect = malloc(sizeof(char *) * (height + 1));
	if (!rect)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		rect[i] = malloc(width + 1);
		if (!rect[i])
			return (free_partial(rect, i), NULL);
		fill_row(rect[i], map[i], width);
	}
	rect[height] = NULL;
	return (rect);
}

void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	flood_check(char **map, int x, int y, int width, int height, int **visited)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return (0);
	if (map[y][x] == ' ')
		return (0);
	if (map[y][x] == '1' || visited[y][x])
		return (1);
	visited[y][x] = 1;
	if (!flood_check(map, x + 1, y, width, height, visited))
		return (0);
	if (!flood_check(map, x - 1, y, width, height, visited))
		return (0);
	if (!flood_check(map, x, y + 1, width, height, visited))
		return (0);
	if (!flood_check(map, x, y - 1, width, height, visited))
		return (0);
	return (1);
}

int	check_walls(char **map, int width, int height, t_player *player)
{
	int	**visited;
	int	result;

	visited = alloc_visited(width, height);
	if (!visited)
		return (0);
	result = flood_check(map, (int)player->px, (int)player->py,
			width, height, visited);
	free_visited(visited, height);
	return (result);
}
