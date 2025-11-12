/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 03:47:14 by aalquraa          #+#    #+#             */
/*   Updated: 2025/11/06 18:02:20 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**copy(char **src, int start, int end)
{
	char	**dest;
	int		i;
	int		j;
	int		len;

	len = end - start;
	dest = malloc(sizeof (char *) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (start < end)
	{
		dest[i] = ft_strdup(src[start++]);
		if (!dest[i])
		{
			j = 0;
			while (j < i)
				free(dest[j++]);
			free(dest);
			return (NULL);
		}
		dest[i] = trim_newline(dest[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

void	split_file(char **file, char ***config, char ***map)
{
	int	i;
	int	map_start;
	int	count;

	i = 0;
	count = 0;
	map_start = -1;
	while (file[i])
	{
		if (is_map(file[i]))
		{
			map_start = i;
			break ;
		}
		i++;
	}
	if (map_start == -1)
	{
		clean_strs(file);
		print_err_and_exit(ERR_MAP);
	}
	while (file[count])
		count++;
	*config = copy(file, 0, map_start);
	if (!*config)
	{
		clean_strs(file);
		print_err_and_exit(ERR_SYS);
	}
	*map = copy(file, map_start, count);
	if (!*map)
	{
		clean_strs(file);
		clean_strs(*config);
		print_err_and_exit(ERR_SYS);
	}
}