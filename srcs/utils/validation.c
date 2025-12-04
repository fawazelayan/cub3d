/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:15:56 by aalquraa          #+#    #+#             */
/*   Updated: 2025/12/05 02:08:11 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_program(int ac, char *filename)
{
	size_t	filename_len;
	char	tmp_buf;
	int		bytes;
	int		fd;

	if (ac != 2)
		print_err_and_exit(ERR_AC);
	filename_len = ft_strlen(filename);
	if (filename_len <= 4)
		print_err_and_exit(ERR_FILE_LEN);
	if (ft_strcmp(filename + filename_len - 4, ".cub"))
		print_err_and_exit(ERR_FILE_EXT);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_err_and_exit(ERR_SYS);
	bytes = read(fd, &tmp_buf, 1);
	if (bytes == 0)
		print_err_and_exit(ERR_FILE_EMPTY);
	if (close(fd) < 0 || bytes < 0)
		print_err_and_exit(ERR_SYS);
}
