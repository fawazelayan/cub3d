/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 05:09:37 by aalquraa          #+#    #+#             */
/*   Updated: 2025/10/18 02:49:18 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


char *skip_space(char *str)
{
    int i;

    i = 0;
    while (str[i] &&(str[i] == ' ' || str[i] == '\t'))
        i++;
    return (str + i);
}

int is_empty_line(char *str)
{
    while (*str)
    {
        if (*str != ' ' && *str != '\t' && *str != '\n')
            return (0);
        str++;
    }
    return (1);
}


char *trim_newline(char *str)
{
    int l;
    
    l = ft_strlen(str);
    if (l > 0 && str[l - 1] == '\n')
        str[l - 1] = '\0';
    return (str);
}

void	free_2d(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_config(t_config *c)
{
    if (!c)
        return ;
    if (c->no)
        free(c->no);
    if (c->so)
        free(c->so);
    if (c->we)
        free(c->we);
    if (c->ea)
        free(c->ea);
}