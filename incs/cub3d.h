/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:52:30 by felayan           #+#    #+#             */
/*   Updated: 2025/12/03 19:34:49 by aalquraa         ###   ########.fr       */
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


# define WE				0
# define NS				1
# define FOV			0.66
# define MOVE_SPEED		0.02
# define SPRINT_SPEED	0.05
# define ROT_SPEED		0.05
# define WIN_HEIGHT		700
# define WIN_WIDTH		1000
// # define TILESIZE	32

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
typedef struct s_ray		t_ray;

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

struct s_ray
{
	double	camera_x; // Represents the x position of the pixels on the plane (-1, 1)
	double	ray_x;	// X pos of ray
	double	ray_y;	// Y pos of ray
	int		map_x;	// Which square the ray is in X
	int		map_y;	// same as above but Y
	double	deltaX;
	double	deltaY;
	int		stepX;
	int		stepY;
	double	sideX;
	double	sideY;
	bool	hit;
	int		side;
	double	wallDist;
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
	double	move_speed;
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
	t_ray		ray;
	mlx_image_t	*img;
	mlx_t		*mlx;
};

void	init_cub3d(t_cub3d *cub);

void	parse_file(t_cub3d *cub, char *filename);
void	split_file(t_cub3d *cub3d, char ***config, char ***map);
char	*trim_newline(char *str);
int 	find_map_start(char **file);
int		count_lines(char **file);
int		is_map(char *line);
void	printf_split(char **split);

int	parse_color(char *line, int *rgb, int *count);
int	validate_config(t_config *config);
int	parse_config_file(t_cub3d *cub, char **config);
int	has_trailing_garbage(char *line);
int	extract_path(char *start, char **path);
int	has_valid_extension(char *path);
int	check_texture_file(char *path);
int	validate_path(char *path);
int	parse_map(t_cub3d *cub3d, char **temp_map);
int	is_valid_char(char m);
int	is_player_char(char p);
int	max_width(char **map);
char	**make_rectangle(char **map, int width, int height);
void	free_visited(int **visited, int height);
int	check_walls(char **map, int width, int height, t_player *player);
int	flood_check(char **map, int x, int y, int width, int height, int **visited);
void	free_visited(int **visited, int height);
int	**alloc_visited(int width, int height);
char *skip_space(char *str);
bool	is_empty_line(char *line);
void	print_err_and_exit(int err);
void	validate_program(int ac, char *filename);
int		count_non_empty_file_lines(int err, char *filename);
void	clean_strs(char **strs);
void	free_map(t_map *map);
void	clean_cub3d(t_cub3d *cub, int err);
void	start_game(t_cub3d *cub);
void	render_floor_ceil(t_cub3d *cub);
void	render_rays(t_cub3d *cub);
void	rotate_right(t_cub3d *cub);
void	move_forward(t_cub3d *cub);
void	move_backward(t_cub3d *cub);
void	move_right(t_cub3d *cub);
void	move_left(t_cub3d *cub);
void	rotate_left(t_cub3d *cub);

#endif