/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 03:11:34 by aalquraa          #+#    #+#             */
/*   Updated: 2025/10/16 03:51:00 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int count_lines(char *name)
{
    int fd;
    int count;
    char *line;

    count = 0;
    fd = open(name, O_RDONLY);
    if (fd < 0)
        exit(1);
    line = get_next_line(fd);
    while(line)
    {
        count++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (count);
}

char **store_file(char *name)
{
    int fd;
    int count;
    char **store;
    char *line;
    int i;
    
    i = 0;
    count = count_lines(name);
    store = malloc(sizeof(char *) * (count + 1));
    if (!store)
        exit(1);
    fd = open(name, O_RDONLY);
    if (fd < 0)
    {
        free(store);
        exit(1);
    }
    line = get_next_line(fd);
    while (line)
    {
        store[i++] = line;
        line = get_next_line(fd);
    }
    store[i] = NULL;
    close(fd);
    return (store);
}

