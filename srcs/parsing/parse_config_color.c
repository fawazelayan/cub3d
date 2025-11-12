/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 06:50:09 by aalquraa          #+#    #+#             */
/*   Updated: 2025/11/06 23:27:15 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	atoi_color(char *str)
{
	int	i;
	int	n;

	i = 0;
	if (!str || !*str)
		return (-1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '\t')
			return (-1);
		i++;
	}
	n = ft_atoi(str);
	if (n < 0 || n > 255)
		return (-1);
	return (n);
}

int	parse_color(char *line, int *rgb, int *count)
{
	char	**clr;
	int		r;
	int		g;
	int		b;

	line++;
	line = skip_space(line);
	clr = ft_split(line, ',');
	if (!clr || !clr[0] || !clr[1] || !clr[2])
	{
		clean_strs(clr);
		return (0);
	}
	r = atoi_color(clr[0]);
	g = atoi_color(clr[1]);
	b = atoi_color(clr[2]);
	if (r == -1 || g == -1 || b == -1)
	{
		clean_strs(clr);
		return (0);
	}
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
	(*count)++;
	clean_strs(clr);
	return (1);
}
