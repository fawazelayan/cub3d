/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 04:31:59 by aalquraa          #+#    #+#             */
/*   Updated: 2025/10/18 02:33:02 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_texture_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	parse_texture(char *line, char **texture)
{
	char	*path;
	char	*start;

	if (*texture != NULL)
		return (0);
	line += 2;
	line = skip_space(line);
	if (!*line || *line == '\n')
		return (0);
	start = line;
	while (*line && *line != ' ' && *line != '\t' && *line != '\n')
		line++;
	path = ft_substr(start, 0, line - start);
	if (!path)
		return (0);
	if (!check_texture_file(path))
	{
		free(path);
		return (0);
	}
	*texture = path;
	return (1);
}
int	parse_config_line(t_config *conf, char *line)
{
	char	*str;

	str = skip_space(line);
	if (!*str || *str == '\n' || is_empty_line(str))
		return (1);
	if (ft_strncmp(str, "NO ", 3) == 0)
		return (parse_texture(str, &conf->no));
	else if (ft_strncmp(str, "SO ", 3) == 0)
		return (parse_texture(str, &conf->so));
	else if (ft_strncmp(str, "WE ", 3) == 0)
		return (parse_texture(str, &conf->we));
	else if (ft_strncmp(str, "EA ", 3) == 0)
		return (parse_texture(str, &conf->ea));
	else if (ft_strncmp(str, "F ", 2) == 0)
		return (parse_color(str, &conf->floor));
	else if (ft_strncmp(str, "C ", 2) == 0)
		return (parse_color(str, &conf->ceiling));
	else
		return (0);
}

int	validate_config(t_config *config)
{
	if (!config->no || !config->so || !config->we || !config->ea)
		return (0);
	if (config->floor.r == -1 || config->floor.g == -1 || config->floor.b == -1)
        return (0);
	if (config->ceiling.r == -1 || config->ceiling.g == -1 || config->ceiling.b == -1)
		return (0);
	return (1);
}


int	parse_config_file(t_cub3d *cub, char **config)
{
	int	i;

	i = 0;
	while (config[i])
	{
		if (!parse_config_line(&cub->config, config[i]))
		{
			printf("Error\nInvalid line in config: %s\n", config[i]);
			return (0);
		}
		i++;
	}
	return (1);
}