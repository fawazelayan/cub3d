/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 04:33:15 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/05 04:58:10 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_line(char *line, int *state, int *count)
{
	if (is_empty_line(line))
	{
		if (*state == 1)
			*state = 2;
	}
	else
	{
		if (*state == 2)
			*state = 3;
		if (is_map_line(line) && *state == 0)
			*state = 1;
		(*count)++;
	}
}

int	count_non_empty_file_lines(int err, char *filename)
{
	char	*line;
	int		count;
	int		fd;
	int		state;

	count = 0;
	state = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd, &err);
	while (line && !err && state != 3)
	{
		process_line(line, &state, &count);
		free(line);
		line = get_next_line(fd, &err);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd, &err);
	}
	if (close(fd) < 0 || err != 0)
		print_err_and_exit(ERR_SYS);
	if (state == 3)
		print_err_and_exit(ERR_MAP);
	return (count);
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
