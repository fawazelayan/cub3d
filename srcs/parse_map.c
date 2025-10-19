/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:56:52 by aalquraa          #+#    #+#             */
/*   Updated: 2025/10/20 00:02:49 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_char(char m)
{
	if (m == '0' || m == '1' || m == 'N'
		|| m == 'S' || m == 'E' || m == 'W' || m == ' ')
		return (1);
	return (0);
}

int	is_player_char(char p)
{
	if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
		return(1);
	return (0);
}
int	find_player(char **map, int *player_x, int *player_y, char *player_dir)
{
	int	i;
	int	j;
	int	p_flag;

	p_flag = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_char(map[i][j]))
			{
				p_flag++;
				*player_x = j;
				*player_y = i;
				*player_dir = map[i][j];
			}
			j++;
		}
		i++;
	}
	if (p_flag != 1)
	{
		if (p_flag == 0)
			printf("Error\nNo player found in map\n");
		else
			printf("Error\nMultiple players found in map\n");
		return (0);
	}
	return (1);
}

int	validate_map(char **map)
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

char	**make_rec(char **map, int width, int height)
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
			rect[i][j++] = ' ';
		rect[i][width] = '\0';
		i++;
	}
	rect[height] = NULL;
	return (rect);
}

int	flood_check(char **map, int x, int y,
		int width, int height, int **visited)
{
	if (x < 0 || y < 0 || y >= height || x >= width)
		return (0);
	if (map[y][x] == ' ')
		return (0);
	if (map[y][x] == '1')
		return (1);
	if (visited[y][x])
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

int	check_walls(char **map, int width, int height, int start_x, int start_y)
{
	int		**visited;
	int		i;
	int		closed;

	visited = malloc(sizeof(int *) * height);
	if (!visited)
	{
		printf("Error\nMemory allocation failed\n");
		return (0);
	}
	i = 0;
	while (i < height)
	{
		visited[i] = ft_calloc(width, sizeof(int));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			printf("Error\nMemory allocation failed\n");
			return (0);
		}
		i++;
	}
	closed = flood_check(map, start_x, start_y, width, height, visited);
	i = 0;
	while (i < height)
		free(visited[i++]);
	free(visited);
	if (!closed)
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
	char	**rectangel;

	height = 0;
	if (!temp_map || !temp_map[0])
	{ printf("Error\nMap is empty\n");
		return (0);
	}
	while (temp_map[height])
		height++;
	if (!validate_map(temp_map))
		return (0);
	if (!find_player(temp_map, &cub3d->map.player_x,
			&cub3d->map.player_y, &cub3d->map.player_dir))
		return (0);
	width = max_width(temp_map);
	rectangel = make_rec(temp_map, width, height);
	if (!rectangel)
	{
		printf("Error\nMemory allocation failed\n");
		return (0);
	}
	if (!check_walls(rectangel, width, height,
			cub3d->map.player_x, cub3d->map.player_y))
	{
		free_2d(rectangel);
		return (0);
	}
	cub3d->map.game_map = rectangel;
	cub3d->map.width = width;
	cub3d->map.height = height;
	return (1);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->game_map)
		free_2d(map->game_map);
	map->game_map = NULL;
	map->width = 0;
	map->height = 0;
}

