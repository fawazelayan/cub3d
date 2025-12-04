/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:16:03 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/04 23:54:19 by felayan          ###   ########.fr       */
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
	lines_count = count_non_empty_file_lines(cub -> err, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_err_and_exit(ERR_SYS);
	cub -> file = malloc(sizeof(char *) * (lines_count + 1));
	if (!cub -> file)
		print_err_and_exit(ERR_SYS);
	line = get_next_line(fd, &cub -> err);
	while (line && !cub -> err)
	{
		if (!is_empty_line(line))
			cub -> file[i++] = line;
		else
			free(line);
		line = get_next_line(fd, &cub -> err);
	}
	cub -> file[i] = NULL;
	if (cub -> err || close(fd) < 0)
		clean_cub3d(cub, ERR_SYS);
}
