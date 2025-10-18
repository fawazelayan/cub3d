/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:41:19 by aalquraa          #+#    #+#             */
/*   Updated: 2025/10/17 03:12:02 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int file_name(char *name, char *ex)
{
    char *str;

    str = ft_strrchr(name, '.');
    if (!str)
    {
        printf("Error\nInvalid file extension\n");
        return (1);
    }
    if (ft_strcmp(str, ex))
    {
        printf("Error\nInvalid file extension\n");
        return (1);
    }
    return (0);
}

int file_check(char *name)
{
    int fd;
    char buffer;
    int byte;
    
    fd = open(name, O_RDONLY);
    if (fd < 0)
    {
        printf("Error\nFile not found or cannot be read.\n");
        return (1);
    }
    byte = read(fd, &buffer, 1);
    if (byte < 0)
    {
        close(fd);
        printf("Error\nFile cannot be read.\n");
        return (1);
    }
    else if (byte == 0)
    {
        close(fd);
        printf("Error\nEmpty file\n");
        return (1);
    }
    close(fd);
    return (0);
}

int validation(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Error\nInvalid number of arguments.\n");
        return (0);
    }
    if (file_name(argv[1], ".cub") || file_check(argv[1]))
        return (0);
    
    return (1);
}