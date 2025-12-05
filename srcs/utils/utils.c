/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:15:54 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/05 04:57:29 by aalquraa         ###   ########.fr       */
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
	else if (err == ERR_MLX)
		ft_putstr_fd(RED"\nError\nMLX failure\n\n", 2);
	exit(err);
}

char	*skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
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
