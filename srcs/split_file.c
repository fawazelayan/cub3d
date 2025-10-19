/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 03:47:14 by aalquraa          #+#    #+#             */
/*   Updated: 2025/10/20 00:14:15 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map(char *line)
{
    int	i;
    int flag;

    line = skip_space(line);
    if (!*line)
        return (0);
    if (*line == '1' || *line == '0')
    {
        i = 0;
        flag = 0;
        while (line[i])
        {
            if (line[i] == '1' || line [i] == '0')
                flag = 1;
            if (line[i] != ' ' && line[i] != '\t' && line[i] != '0' && line[i] != '1'
                && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
                return (0);
            i++;
        }
        return (flag);
    }
    return (0);
}

char **copy(char **src, int start, int end)
{
    char **dest;
    int i;
    int j;
    int len;
    
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

void split_file(char **file, char ***config, char ***map)
{
    int i;
    int map_start;
    int count;
    
    i = 0;
    count = 0;
    map_start = -1;
    while (file[i])
    {
        if (is_map(file[i]))
        {
            map_start = i;
            break;
        }
        i++;
    }
    if (map_start == -1)
    {
        free_2d(file);
        printf("Error\nMap not found\n");
        exit(1);
    }
    while (file[count])
        count++;
    *config = copy(file, 0, map_start);
    if (!*config)
    {
        free_2d(file);
        printf("Error\nMemory allocation failed\n");
        exit(1);
    }
    *map = copy(file, map_start, count);
    if (!*map)
    {
        free_2d(file);
        free_2d(*config);
        printf("Error\nMemory allocation failed\n");
        exit(1);
    }
}
