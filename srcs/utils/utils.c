/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:15:54 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/03 02:38:10 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_err_and_exit(int err)
{
	if (err == ERR_AC)
		ft_putstr_fd(RED"\nError\nUsage: [./cub3D <map>]\n\n"RST, 2);
	else if (err == ERR_FILE_LEN)
		ft_putstr_fd(RED"\nError\nFile name must be longer \n\n"RST, 2);
	else if (err == ERR_FILE_EXT)
		ft_putstr_fd(RED"\nError\nExtension must be (.cub)\n\n"RST, 2);
	else if (err == ERR_FILE_EMPTY)
		ft_putstr_fd(RED"\nError\nFile empty\n\n", 2);
	else if (err == ERR_SYS)
	{
		ft_putstr_fd(RED"\nError\n", 2);
		perror("cub3D");
		ft_putstr_fd("\n"RST, 2);
	}
	else if (err == ERR_MAP)
		ft_putstr_fd(RED"\nError\nInvalid map\n\n", 2);
	else if (err == ERR_CONFIG)
		ft_putstr_fd(RED"\nError\nInvalid Config\n\n", 2);
	else if (err == ERR_MLX_INIT)
		ft_putstr_fd(RED"\nError\nMLX init failure\n\n", 2);
	else if (err == ERR_MAIN_IMG_CRT)
		ft_putstr_fd(RED"\nError\nMLX main image failure\n\n", 2);
	exit(err);
}

char	*skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] &&(str[i] == ' ' || str[i] == '\t'))
		i++;
	return (str + i);
}

bool	is_map_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (!line[i])
		return (false);
	while (line[i])
	{
		if (!ft_strchr(" 10NSWE\n", line[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
			return (false);
		i++;
	}
	return (true);
}

int	count_non_empty_file_lines(int err, char *filename)
{
	char	*line;
	int		count;
	int		fd;
	bool	map_started;
	bool	empty_after_map;
	bool	false_map;

	count = 0;
	false_map = false;
	map_started = false;
	empty_after_map = false;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd, &err);
	while (line && !err && !false_map)
	{
		if (is_empty_line(line))
		{
			if (map_started)
				empty_after_map = true;
		}
		else
		{
			if (empty_after_map && !is_empty_line(line))
				false_map = true;
			if (is_map_line(line))
				map_started = true;
			count++;
		}
		free(line);
		line = get_next_line(fd, &err);
	}
    while (line)
    {
        free(line);
        line = get_next_line(fd, &err);
	}
	if (close(fd) < 0)
		err = ERR_SYS;
	if (err != 0)
		print_err_and_exit(ERR_SYS);
	if (false_map)
		print_err_and_exit(ERR_MAP);
	return (count);
}

char	*trim_newline(char *str)
{
	int	l;

	if (!str)
		return (NULL);
	l = ft_strlen(str);
	if (l > 0 && str[l - 1] == '\n')
		str[l - 1] = '\0';
	return (str);
}

int	find_map_start(char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (is_map(file[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	count_lines(char **file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	return (i);
}

int	is_map(char *line)
{
	int	i;
	int	flag;

	line = skip_space(line);
	if (!*line)
		return (0);
	if (*line == '1' || *line == '0')
	{
		i = 0;
		flag = 0;
		while (line[i])
		{
			if (line[i] == '1')
				flag = 1;
			if (!ft_strchr(" 01NSEW\n\t", line[i]))
				return (0);
			i++;
		}
		return (flag);
	}
	return (0);
}


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

