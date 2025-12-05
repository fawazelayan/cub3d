/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 04:29:45 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/05 04:56:59 by aalquraa         ###   ########.fr       */
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

int	has_valid_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strcmp(path + len - 4, ".png") != 0)
		return (0);
	return (1);
}

int	extract_path(char *start, char **path)
{
	int		len;
	char	*tmp;

	len = 0;
	while (start[len]
		&& start[len] != ' '
		&& start[len] != '\t'
		&& start[len] != '\n')
		len++;
	tmp = ft_substr(start, 0, len);
	if (!tmp)
		return (0);
	*path = tmp;
	return (1);
}

int	has_trailing_garbage(char *line)
{
	line = skip_space(line);
	if (*line && *line != '\n')
		return (1);
	return (0);
}

int	validate_path(char *path)
{
	if (!has_valid_extension(path))
		return (0);
	if (!check_texture_file(path))
		return (0);
	return (1);
}
