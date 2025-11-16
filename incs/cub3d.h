/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:52:30 by felayan           #+#    #+#             */
/*   Updated: 2025/11/17 00:52:35 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ERR_CONFIG			30
# define ERR_MAP			31

# define ERR_FILE_EMPTY		40
# define ERR_FILE_LEN		41
# define ERR_FILE_EXT		42
# define ERR_SYS			43
# define ERR_AC				44

# define ERR_MLX_INIT		50
# define ERR_MAIN_IMG_CRT	51
# define ERR_NO_TEXTURE_LD	52
# define ERR_SO_TEXTURE_LD	53
# define ERR_WE_TEXTURE_LD	54
# define ERR_EA_TEXTURE_LD	55


# define FOV		0.66
# define MOVE_SPEED 0.2
# define ROT_SPEED	0.1
# define WIN_HEIGHT	700
# define WIN_WIDTH	900
# define TILESIZE	32

# define RED	"\033[0;31m"
# define RST	"\033[0m"

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

typedef struct s_assets	t_assets;
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

struct s_assets
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
	double	plane_x;
	double	plane_y;
	double	dirx;
	double	diry;
	char	dir;
	double	px;
	double	py;
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
	t_assets	ass;
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
void	start_game(t_cub3d *cub);

#endif