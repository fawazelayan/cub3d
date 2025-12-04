/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 04:31:59 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/05 02:41:55 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(char *line, char **texture)
{
	char	*path;

	if (*texture != NULL)
		return (0);
	line += 2;
	line = skip_space(line);
	if (!*line || *line == '\n')
		return (0);
	if (!extract_path(line, &path))
		return (0);
	if (!validate_path(path))
	{
		free(path);
		return (0);
	}
	line += ft_strlen(path);
	if (has_trailing_garbage(line))
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
	if (str[0] == 'N' && str[1] == 'O' && (str[2] == ' ' || str[2] == '\t'))
		return (parse_texture(str, &conf->no_conf));
	else if (str[0] == 'S' && str[1] == 'O'
		&& (str[2] == ' ' || str[2] == '\t'))
		return (parse_texture(str, &conf->so_conf));
	else if (str[0] == 'W' && str[1] == 'E'
		&& (str[2] == ' ' || str[2] == '\t'))
		return (parse_texture(str, &conf->we_conf));
	else if (str[0] == 'E' && str[1] == 'A'
		&& (str[2] == ' ' || str[2] == '\t'))
		return (parse_texture(str, &conf->ea_conf));
	else if (str[0] == 'F' && (str[1] == ' ' || str[1] == '\t'))
		return (parse_color(str, conf->f_rgb, &conf->f_count));
	else if (str[0] == 'C' && (str[1] == ' ' || str[1] == '\t'))
		return (parse_color(str, conf->c_rgb, &conf->c_count));
	else
		return (0);
}

int	validate_config(t_config *conf)
{
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
			return (0);
		i++;
	}
	if (!validate_config(&cub->config))
		return (0);
	return (1);
}
