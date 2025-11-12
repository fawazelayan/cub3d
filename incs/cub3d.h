/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:52:30 by felayan           #+#    #+#             */
/*   Updated: 2025/11/06 23:27:54 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # define ERR_MAP_MANYPLR		30
// # define ERR_MAP_INVCHR		31
// # define ERR_MAP_CLOSED		32
// # define ERR_MAP_FIRST		33
// # define ERR_MAP_SPLIT		34
// # define ERR_MAP_NOPLR		35
// # define ERR_MAP_SPACE		36
// # define ERR_MAP_NONE		37

# define ERR_MAP 30
# define ERR_COF 77
# define ERR_FILE_EMPTY		40
# define ERR_FILE_LEN		41
# define ERR_FILE_EXT		42
# define ERR_SYS			43
# define ERR_AC				44

# define RED	"\033[0;31m"
# define RST	"\033[0m"

# define WIN_HEIGHT 700
# define WIN_WIDTH 900
# define TILESIZE 32
# define FOV 0.6

# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h> // Might not be needed
# include <math.h>
# include "get_next_line.h"
# include "libft.h"
# include "MLX42.h"

typedef struct s_textures	t_textures;
typedef struct s_config		t_config;
typedef struct s_player		t_player;
typedef struct s_cub3d		t_cub3d;
typedef struct s_map		t_map;

struct s_config
{
	char	*no_conf;
	char	*so_conf;
	char	*ea_conf;
	char	*we_conf;
	int		f_rgb[3];
	int		c_rgb[3];
	int		c_count;
	int		f_count;
};

struct s_textures
{
	mlx_texture_t	*no_tex;
	mlx_texture_t	*so_tex;
	mlx_texture_t	*we_tex;
	mlx_texture_t	*ea_tex;
	uint32_t		f_color;
	uint32_t		c_color;
};

struct s_player
{
	float	plane_x;
	float	plane_y;
	float	angle;
	float	dirx;
	float	diry;
	float	px;
	float	py;
};

struct s_map
{
	char	**grid;
	int		height;
	int		width;
};

struct s_cub3d
{
	int			my_errno;
	char		**file;
	t_config	config;
	t_player	player;
	t_textures	texs;
	t_map		map;
	mlx_image_t	*img;
	mlx_t		*mlx;
};

void	init_cub3d(t_cub3d *cub);

void	parse_file(t_cub3d *cub, char *filename);
void	split_file(char **file, char ***config, char ***map);


int	parse_color(char *line, int *rgb, int *count);
int	validate_config(t_config *config);
int	parse_config_file(t_cub3d *cub, char **config);

int	parse_map(t_cub3d *cub3d, char **temp_map);
char *skip_space(char *str);
bool	is_empty_line(char *line);
void	print_err_and_exit(int err);
void	validate_program(int ac, char *filename);
int		count_non_empty_file_lines(int err, char *filename);
void	clean_strs(char **strs);
void	free_map(t_map *map);
void	clean_cub3d(t_cub3d *cub, int err);

#endif