/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:52:30 by felayan           #+#    #+#             */
/*   Updated: 2025/10/19 23:06:29 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h> // Might not be needed
#include <math.h>
#include "get_next_line.h"
#include "libft.h"
#include "MLX42.h"

typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_config
{
    char *no;
    char *so;
    char *ea;
    char *we;
    t_color floor;
    t_color ceiling;
} t_config;

typedef struct s_map
{
    char **game_map;
    int width;
    int height;
    int player_x;
    int player_y;
    char player_dir;
} t_map;

typedef struct s_cub3d
{
    t_config config;
    t_map map;
} t_cub3d;

int validation(int argc, char **argv);
char **store_file(char *name);
void split_file(char **file, char ***config, char ***map);
void init(t_cub3d *cub3d);
int parse_config_file(t_cub3d *cub, char **config);
int parse_color(char *line, t_color *color);
void free_config(t_config *c);

int parse_map(t_cub3d *cub, char **map_raw);
void free_map(t_map *map);

char *skip_space(char *str);
int is_empty_line(char *str);
char *trim_newline(char *str);
void free_2d(char **str);
int validate_config(t_config *config);

#endif