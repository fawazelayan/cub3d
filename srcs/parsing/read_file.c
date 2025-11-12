/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:16:03 by aalquraa          #+#    #+#             */
/*   Updated: 2025/11/06 22:18:44 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_file(t_cub3d *cub, char *filename)
{
	int		lines_count;
	int		fd;
	char	*line;
	int		i;

	i = 0;
	lines_count = count_non_empty_file_lines(cub -> my_errno, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_err_and_exit(ERR_SYS);
	cub -> file = malloc(sizeof(char *) * (lines_count + 1));
	if (!cub -> file)
		print_err_and_exit(ERR_SYS);
	line = get_next_line(fd, &cub -> my_errno);
	while (line && !cub -> my_errno)
	{
		if (!is_empty_line(line))
			cub -> file[i++] = line;
		else
			free(line);
		line = get_next_line(fd, &cub -> my_errno);
	}
	cub -> file[i] = NULL;
	if (cub -> my_errno || close(fd) < 0)
		clean_cub3d(cub, ERR_SYS);
}
