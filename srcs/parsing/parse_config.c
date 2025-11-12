/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 04:31:59 by aalquraa          #+#    #+#             */
/*   Updated: 2025/11/13 02:02:35 by aalquraa         ###   ########.fr       */
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
	int		len;

	len = 0;
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
	len = ft_strlen(path);
	if (len < 4 || ft_strcmp(path + len - 4, ".png"))
	{
		free(path);
		return (0);
	}
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
		return (parse_texture(str, &conf->no_conf));
	else if (ft_strncmp(str, "SO ", 3) == 0)
		return (parse_texture(str, &conf->so_conf));
	else if (ft_strncmp(str, "WE ", 3) == 0)
		return (parse_texture(str, &conf->we_conf));
	else if (ft_strncmp(str, "EA ", 3) == 0)
		return (parse_texture(str, &conf->ea_conf));
	else if (ft_strncmp(str, "F ", 2) == 0)
		return (parse_color(str, conf->f_rgb, &conf->f_count));
	else if (ft_strncmp(str, "C ", 2) == 0)
		return (parse_color(str, conf->c_rgb, &conf->c_count));
	else
		return (0);
}

int	validate_config(t_config *conf)
{
	// change to ERR_CONF
	if (conf->c_count != 1 || conf->f_count != 1)
		return (0);
	if (!conf->no_conf || !conf->so_conf || !conf->we_conf || !conf->ea_conf)
		return (0);	
	if (conf->f_rgb[0] == -1 || conf->f_rgb[1] == -1 || conf->f_rgb[2] == -1)
		return (0);
	if (conf->c_rgb[0] == -1 || conf->c_rgb[1] == -1 || conf->c_rgb[2] == -1)
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
			return (0);
		}
		i++;
	}
	if (!validate_config(&cub->config))// remove ! later.
		return (0);
	return (1);
}