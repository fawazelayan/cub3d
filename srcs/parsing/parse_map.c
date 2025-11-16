/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:56:52 by aalquraa          #+#    #+#             */
/*   Updated: 2025/11/17 00:40:37 by felayan          ###   ########.fr       */
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

static int	find_player(char **map, t_player *player)
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
				player->px = j + 0.5;
				player->py = i + 0.5;
				player->dir = map[i][j];
			}
			j++;
		}
		i++;
	}
	if (flag != 1)
	{
		if (flag == 0)
			printf("Error\nNo player found in map\n");
		else
			printf("Error\nMultiple players found in map\n");
		return (0);
	}
	return (1);
}

static int	validate_map_chars(char **map)
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
			{
				printf("Error\nInvalid character in map: '%c'\n", map[i][j]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	max_width(char **map)
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

char	**make_rectangle(char **map, int width, int height)
{
	char	**rect;
	int		i;
	int		j;
	int		len;

	rect = malloc(sizeof(char *) * (height + 1));
	if (!rect)
		return (NULL);
	i = 0;
	while (i < height)
	{
		rect[i] = malloc(width + 1);
		if (!rect[i])
		{
			while (--i >= 0)
				free(rect[i]);
			free(rect);
			return (NULL);
		}
		len = ft_strlen(map[i]);
		j = 0;
		while (j < len)
		{
			rect[i][j] = map[i][j];
			j++;
		}
		while (j < width)
		{
			rect[i][j] = ' ';
			j++;
		}
		rect[i][width] = '\0';
		i++;
	}
	rect[height] = NULL;
	return (rect);
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
	int	i;
	int	result;

	visited = malloc(sizeof(int *) * height);
	if (!visited)
		return (0);
	i = 0;
	while (i < height)
	{
		visited[i] = ft_calloc(width, sizeof(int));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (0);
		}
		i++;
	}
	result = flood_check(map, (int)player->px, (int)player->py, width, height,
			visited);
	i = 0;
	while (i < height)
		free(visited[i++]);
	free(visited);
	if (!result)
	{
		printf("Error\nMap is not closed (leak detected)\n");
		return (0);
	}
	return (1);
}

int	parse_map(t_cub3d *cub3d, char **temp_map)
{
	int		height;
	int		width;
	char	**rect_map;

	if (!temp_map || !temp_map[0])
	{
		printf("Error\nMap is empty\n");
		return (0);
	}
	if (!validate_map_chars(temp_map))
		return (0);
	if (!find_player(temp_map, &cub3d->player))
		return (0);
	height = 0;
	while (temp_map[height])
		height++;
	width = max_width(temp_map);
	rect_map = make_rectangle(temp_map, width, height);
	if (!rect_map)
	{
		printf("Error\nMemory allocation failed\n");
		return (0);
	}
	if (!check_walls(rect_map, width, height, &cub3d->player))
	{
		clean_strs(rect_map);
		return (0);
	}
	cub3d->map.grid = rect_map;
	cub3d->map.width = width;
	cub3d->map.height = height;
	return (1);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->grid)
		clean_strs(map->grid);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
}
