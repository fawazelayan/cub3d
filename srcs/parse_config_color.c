/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 06:50:09 by aalquraa          #+#    #+#             */
/*   Updated: 2025/10/18 02:43:35 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	atoi_color(char *str)
{
	int	i;
	int	n;

	i = 0;
	if (!str || !*str)
		return (-307);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '\t')
			return (-307);
		i++;
	}
	n = ft_atoi(str);
	if (n < 0 || n > 255)
		return (-307);
	return (n);
}

int	parse_color(char *line, t_color *color)
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
		free_2d(clr);
		return (0);
	}
	r = atoi_color(clr[0]);
	g = atoi_color(clr[1]);
	b = atoi_color(clr[2]);
	if (r == -307 || g == -307 || b == -307)
	{
		free_2d(clr);
		return (0);
	}
	color->r = r;
	color->g = g;
	color->b = b;
	free_2d(clr);
	return (1);
}
