/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:52:30 by felayan           #+#    #+#             */
/*   Updated: 2025/12/06 14:52:08 by felayan          ###   ########.fr       */
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
# define HEIGHT			700
# define WIDTH			900

# define RED	"\033[0;31m"
# define RST	"\033[0m"

# include "get_next_line.h"
# include "libft.h"
# include "MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_assets		t_assets;
typedef struct s_config		t_config;
typedef struct s_player		t_player;
typedef struct s_render		t_render;
typedef struct s_cub3d		t_cub3d;
typedef struct s_map		t_map;
typedef struct s_ray		t_ray;
typedef struct s_flood		t_flood;

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
	double	raydirx;
	double	raydiry;
	double	cam_x;
	int		stepx;
	int		stepy;
	int		mapx;
	int		mapy;
	int		side;
	bool	hit;
};

struct s_render
{
	double			wall_hitp;
	double			tex_pos;
	double			scale;
	int				draw_end;
	int				draw_st;
	int				pixel_x;
	int				pixel_y;
	int				wall_h;
	int				tex_x;
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

struct s_flood
{
	char	**map;
	int		**visited;
	int		height;
	int		width;
};

struct s_cub3d
{
	t_config	config;
	t_player	pl;
	t_render	render;
	t_assets	ass;
	t_map		map;
	t_ray		ray;
	mlx_image_t	*img;
	mlx_t		*mlx;
	char		**file;
	int			err;
};

uint32_t	get_rgb(int rgb[]);

void		init_player(t_player *pl);
void		init_cub3d(t_cub3d *cub);
void		init_mlx(t_cub3d *cub);

void		split_file(t_cub3d *cub3d, char ***config, char ***map);
void		parse_file(t_cub3d *cub, char *filename);
int			parse_config_file(t_cub3d *cub, char **config);
int			parse_color(char *line, int *rgb, int *count);
int			parse_map(t_cub3d *cub3d, char **temp_map);
int			find_map_start(char **file);
int			count_lines(char **file);
int			is_map(char *line);
char		*trim_newline(char *str);

int			check_walls(char **map, int width, int height, t_player *pl);
int			count_non_empty_file_lines(int err, char *filename);
int			flood_check(int x, int y, t_flood *flood);
int			**alloc_visited(int width, int height);
int			extract_path(char *start, char **path);
int			validate_config(t_config *config);
int			has_trailing_garbage(char *line);
int			has_valid_extension(char *path);
int			check_texture_file(char *path);
int			validate_path(char *path);
int			is_valid_char(char m);
int			is_player_char(char p);
int			max_width(char **map);
char		**make_rectangle(char **map, int width, int height);
char		*skip_space(char *str);
void		fill_row(char *dst, char *src, int width);
void		validate_program(int ac, char *filename);
void		free_visited(int **visited, int height);
void		free_visited(int **visited, int height);
void		free_partial(char **rect, int i);
void		print_err_and_exit(int err);
bool		is_map_line(const char *line);
bool		is_empty_line(char *line);

void		calculate_hitpoint(t_ray *ray, t_render *ren, t_player *pl);
void		get_texture(t_ray *ray, t_render *ren, t_assets *ass);
void		render_floor_ceil(mlx_image_t *img, t_assets *ass);
void		draw(t_render *ren, mlx_image_t *img, int x);
void		calculate_dist(t_ray *ray, t_player *pl);
void		perform_dda(t_ray *ray, t_map *map);
void		start_game(t_cub3d *cub);
void		render_rays(t_cub3d *cub);

void		move_backward(t_player *pl, mlx_t *mlx, t_map *map);
void		move_forward(t_player *pl, mlx_t *mlx, t_map *map);
void		move_right(t_player *pl, mlx_t *mlx, t_map *map);
void		move_left(t_player *pl, mlx_t *mlx, t_map *map);
void		esc_press(mlx_key_data_t keydata, void *param);
void		rotate_right(t_player *pl);
void		rotate_left(t_player *pl);
void		end_game(void *param);

void		clean_cub3d(t_cub3d *cub, int err);
void		clean_strs(char **strs);

#endif