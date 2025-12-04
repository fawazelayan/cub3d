/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:52:30 by felayan           #+#    #+#             */
/*   Updated: 2025/12/05 02:42:41 by felayan          ###   ########.fr       */
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

# define ERR_MLX			50

# define WE				0
# define NS				1
# define ROT_SPEED		0.05
# define MOVE_SPEED		0.05
# define SPRINT_SPEED	0.15
# define FOV			0.66
# define WIN_HEIGHT		700
# define WIN_WIDTH		900

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

typedef struct s_assets		t_assets;
typedef struct s_config		t_config;
typedef struct s_player		t_player;
typedef struct s_render		t_render;
typedef struct s_cub3d		t_cub3d;
typedef struct s_map		t_map;
typedef struct s_ray		t_ray;

struct s_config
{
	int		f_rgb[3];
	int		c_rgb[3];
	int		c_count;
	int		f_count;
	char	*no_conf;
	char	*so_conf;
	char	*ea_conf;
	char	*we_conf;
};

struct s_ray
{
	double	dlta_distx;
	double	dlta_disty;
	double	side_distx;
	double	side_disty;
	double	wall_dist;
	double	camera_x;
	double	raydirx;
	double	raydiry;
	int		stepx;
	int		stepy;
	int		mapx;
	int		mapy;
	int		side;
	bool	hit;
};

struct s_render
{
	int				wall_height;
	int				draw_start;
	int				draw_end;
	int				pixel_x;
	int				pixel_y;
	mlx_texture_t	*tex;
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
	double	move_speed;
	double	planex;
	double	planey;
	double	dirx;
	double	diry;
	double	px;
	double	py;
	char	dir;
};

struct s_map
{
	int		height;
	int		width;
	char	**grid;
};

struct s_cub3d
{
	t_config	config;
	t_player	player;
	t_render	render;
	t_assets	ass;
	t_map		map;
	t_ray		ray;
	mlx_image_t	*img;
	mlx_t		*mlx;
	char		**file;
	int			err;
};

void		init_cub3d(t_cub3d *cub);

void		parse_file(t_cub3d *cub, char *filename);
void		split_file(t_cub3d *cub3d, char ***config, char ***map);
char		*trim_newline(char *str);
int			find_map_start(char **file);
int			count_lines(char **file);
int			is_map(char *line);
void		printf_split(char **split);

int			parse_color(char *line, int *rgb, int *count);
int			validate_config(t_config *config);
int			parse_config_file(t_cub3d *cub, char **config);
int			has_trailing_garbage(char *line);
int			extract_path(char *start, char **path);
int			has_valid_extension(char *path);
int			check_texture_file(char *path);
int			validate_path(char *path);
int			parse_map(t_cub3d *cub3d, char **temp_map);
int			is_valid_char(char m);
int			is_player_char(char p);
int			max_width(char **map);
char		**make_rectangle(char **map, int width, int height);
void		free_visited(int **visited, int height);
int			check_walls(char **map, int width, int height, t_player *player);
int			flood_check(char **map, int x, int y, int width, int height, int **visited);
void		free_visited(int **visited, int height);
int			**alloc_visited(int width, int height);
char		*skip_space(char *str);
bool		is_empty_line(char *line);
void		print_err_and_exit(int err);
void		validate_program(int ac, char *filename);
int			count_non_empty_file_lines(int err, char *filename);
void		clean_strs(char **strs);
void		init_mlx(t_cub3d *cub);
void		init_player(t_player *pl);
// void	free_map(t_map *map);
void		calculate_dist(t_ray *ray, t_player *pl);
void		perform_dda(t_ray *ray, t_map *map);
void		get_texture(t_ray *ray, t_render *ren, t_assets *ass);

void		clean_cub3d(t_cub3d *cub, int err);
void		start_game(t_cub3d *cub);
void		render_floor_ceil(mlx_image_t *img, t_assets *ass);
void		render_rays(t_cub3d *cub);
void		rotate_right(t_player *pl);
void		move_forward(t_player *pl, mlx_t *mlx, t_map *map);
void		move_backward(t_player *pl, mlx_t *mlx, t_map *map);
void		move_right(t_player *pl, mlx_t *mlx, t_map *map);
void		move_left(t_player *pl, mlx_t *mlx, t_map *map);
void		rotate_left(t_player *pl);
uint32_t	get_rgb(int rgb[]);
void		end_game(void *param);
void		esc_press(mlx_key_data_t keydata, void *param);

#endif