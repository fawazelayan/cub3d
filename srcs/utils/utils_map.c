/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:05:16 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/06 14:05:59 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	flood_check(int x, int y, t_flood *flood)
{
	if (x < 0 || y < 0 || x >= flood->width || y >= flood->height)
		return (0);
	if (flood->map[y][x] == ' ')
		return (0);
	if (flood->map[y][x] == '1' || flood->visited[y][x])
		return (1);
	flood->visited[y][x] = 1;
	if (!flood_check(x + 1, y, flood))
		return (0);
	if (!flood_check(x - 1, y, flood))
		return (0);
	if (!flood_check(x, y + 1, flood))
		return (0);
	if (!flood_check(x, y - 1, flood))
		return (0);
	return (1);
}

int	check_walls(char **map, int width, int height, t_player *pl)
{
	int		**visited;
	int		result;
	t_flood	flood;

	visited = alloc_visited(width, height);
	if (!visited)
		return (0);
	flood.map = map;
	flood.width = width;
	flood.height = height;
	flood.visited = visited;
	result = flood_check((int)pl->px, (int)pl->py, &flood);
	free_visited(visited, height);
	return (result);
}
