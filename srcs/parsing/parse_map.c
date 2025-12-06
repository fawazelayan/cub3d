/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:56:52 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/06 14:05:59 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_player(char **map, t_player *pl)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_char(map[i][j]))
			{
				flag++;
				pl->px = j + 0.5;
				pl->py = i + 0.5;
				pl->dir = map[i][j];
			}
			j++;
		}
		i++;
	}
	if (flag != 1)
		return (0);
	return (1);
}

int	validate_map_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_char(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	**alloc_visited(int width, int height)
{
	int	**visited;
	int	i;

	visited = malloc(sizeof(int *) * height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = ft_calloc(width, sizeof(int));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

int	get_height(char **map)
{
	int	h;

	h = 0;
	while (map[h])
		h++;
	return (h);
}

int	parse_map(t_cub3d *cub3d, char **temp_map)
{
	char	**rect;
	int		height;
	int		width;

	if (!temp_map || !temp_map[0])
		return (0);
	if (!validate_map_chars(temp_map))
		return (0);
	if (!find_player(temp_map, &cub3d->pl))
		return (0);
	height = get_height(temp_map);
	width = max_width(temp_map);
	rect = make_rectangle(temp_map, width, height);
	if (!rect)
		return (0);
	if (!check_walls(rect, width, height, &cub3d->pl))
	{
		clean_strs(rect);
		return (0);
	}
	cub3d->map.grid = rect;
	cub3d->map.width = width;
	cub3d->map.height = height;
	return (1);
}
