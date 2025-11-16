/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:42:07 by aalquraa          #+#    #+#             */
/*   Updated: 2025/11/17 00:48:25 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	printf_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		printf("%s", split[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_cub3d	cub3d;
	char	**config;
	char	**map;

	validate_program(ac, av[1]);
	init_cub3d(&cub3d);
	parse_file(&cub3d, av[1]);
	split_file(cub3d.file, &config, &map);
	clean_strs(cub3d.file);
	cub3d.file = NULL;
	if (!parse_config_file(&cub3d, config) || !validate_config(&cub3d.config))
	{
		clean_strs(config);
		clean_strs(map);
		clean_cub3d(&cub3d, ERR_CONFIG);
	}
	if (!parse_map(&cub3d, map))
	{
		clean_strs(config);
		clean_strs(map);
		clean_cub3d(&cub3d, ERR_MAP);
	}
	//printf_split(config);
	// printf("%s\n", cub3d.config.no_conf);
	// printf("%s\n", cub3d.config.so_conf);
	// printf("%s\n", cub3d.config.we_conf);
	// printf("%s\n", cub3d.config.ea_conf);
	// for(int i = 0; i < 3; i++)
	// {
	// 	printf("%d ", cub3d.config.c_rgb[i]);
	// } 
	// printf("\n");
	// for(int i = 0; i < 3; i++)
	// {
	// 	printf("%d ", cub3d.config.f_rgb[i]);
	// }
	start_game(&cub3d);
	clean_strs(config);
	clean_strs(map);
	clean_cub3d(&cub3d, EXIT_SUCCESS);
	return (0);
}







// int main(int argc, char **argv)
// {
// 	if (!validation(argc, argv))
// 		exit(EXIT_FAILURE);
// }


// #define BASE_W 900
// #define BASE_H 700
// #define FOV 0.66     //  ~66° field of view
// #define SPEED 0.05
// #define ROT_SPEED 0.04

// typedef struct s_game
// {
// 	mlx_t          *mlx;
// 	mlx_image_t    *img;
// 	mlx_texture_t  *tex[4];   // N,S,E,W
// 	double          px, py;   // player position
// 	double          dirx, diry;
// 	double          planex, planey;
// 	int             width, height;
// }	t_game;

// /* ---------------------------------------------------- */

// static uint32_t	get_tex_pixel(mlx_texture_t *t, int x, int y)
// {
// 	uint8_t *p = &t->pixels[(y * t->width + x) * 4];
// 	return (p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3]);
// }

// /* draw one wall slice according to hit side and distance */
// static void	draw_column(t_game *g, int x, double dist, int side, double wallx)
// {
// 	int line_h = (int)(g->height / dist);
// 	int draw_start = -line_h / 2 + g->height / 2;
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	int draw_end = line_h / 2 + g->height / 2;
// 	if (draw_end >= g->height)
// 		draw_end = g->height - 1;

// 	mlx_texture_t *tex = g->tex[side];
// 	int tex_x = (int)(wallx * tex->width);
// 	if ((side == 0 || side == 1) && g->dirx > 0) tex_x = tex->width - tex_x - 1;
// 	if ((side == 2 || side == 3) && g->diry < 0) tex_x = tex->width - tex_x - 1;

// 	for (int y = 0; y < g->height; ++y)
// 	{
// 		uint32_t color;
// 		if (y < draw_start)
// 			color = 0xAAAAAAFF;            // ceiling
// 		else if (y > draw_end)
// 			color = 0x444444FF;            // floor
// 		else
// 		{
// 			double tex_y = ((y - draw_start) * tex->height) / (double)line_h;
// 			color = get_tex_pixel(tex, tex_x, (int)tex_y);
// 		}
// 		mlx_put_pixel(g->img, x, y, color);
// 	}
// }

// /* ---------------------------------------------------- */
// /* very small "world": one vertical wall at x=1 running north-south */

// static int	world_map(double x, double y)
// {
// 	if (x < 1.0) return 1;   // wall at x = 1
// 	if (x > 4.0 || y < 0.0 || y > 4.0) return 1; // border
// 	return 0;
// }

// /* main raycasting loop for one frame */
// static void	render_scene(t_game *g)
// {
// 	mlx_delete_image(g->mlx, g->img);
// 	g->img = mlx_new_image(g->mlx, g->width, g->height);

// 	for (int x = 0; x < g->width; x++)
// 	{
// 		double camera_x = 2 * x / (double)g->width - 1;
// 		double ray_dir_x = g->dirx + g->planex * camera_x;
// 		double ray_dir_y = g->diry + g->planey * camera_x;

// 		int map_x = (int)g->px;
// 		int map_y = (int)g->py;

// 		double delta_x = fabs(1 / ray_dir_x);
// 		double delta_y = fabs(1 / ray_dir_y);
// 		double side_dist_x, side_dist_y;
// 		int step_x, step_y, hit = 0, side = 0;

// 		if (ray_dir_x < 0) { step_x = -1; side_dist_x = (g->px - map_x) * delta_x; }
// 		else { step_x = 1; side_dist_x = (map_x + 1.0 - g->px) * delta_x; }
// 		if (ray_dir_y < 0) { step_y = -1; side_dist_y = (g->py - map_y) * delta_y; }
// 		else { step_y = 1; side_dist_y = (map_y + 1.0 - g->py) * delta_y; }

// 		while (!hit)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{ side_dist_x += delta_x; map_x += step_x; side = (step_x < 0) ? 0 : 1; }
// 			else
// 			{ side_dist_y += delta_y; map_y += step_y; side = (step_y < 0) ? 2 : 3; }
// 			if (world_map(map_x, map_y)) hit = 1;
// 		}

// 		double perp_dist;
// 		if (side == 0 || side == 1)
// 			perp_dist = (map_x - g->px + (1 - step_x) / 2) / ray_dir_x;
// 		else
// 			perp_dist = (map_y - g->py + (1 - step_y) / 2) / ray_dir_y;

// 		double wallx;
// 		if (side == 0 || side == 1)
// 			wallx = g->py + perp_dist * ray_dir_y;
// 		else
// 			wallx = g->px + perp_dist * ray_dir_x;
// 		wallx -= floor(wallx);

// 		draw_column(g, x, perp_dist, side, wallx);
// 	}
// 	mlx_image_to_window(g->mlx, g->img, 0, 0);
// }

// /* ---------------------------------------------------- */

// static void	move_player(t_game *g)
// {
// 	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
// 	{
// 		g->px += g->dirx * SPEED;
// 		g->py += g->diry * SPEED;
// 	}
// 	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
// 	{
// 		g->px -= g->dirx * SPEED;
// 		g->py -= g->diry * SPEED;
// 	}
// 	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
// 	{
// 		g->px -= g->planex * SPEED;
// 		g->py -= g->planey * SPEED;
// 	}
// 	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
// 	{
// 		g->px += g->planex * SPEED;
// 		g->py += g->planey * SPEED;
// 	}
// 	double old_dirx, old_planex;
// 	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
// 	{
// 		old_dirx = g->dirx;
// 		g->dirx = g->dirx * cos(ROT_SPEED) - g->diry * sin(ROT_SPEED);
// 		g->diry = old_dirx * sin(ROT_SPEED) + g->diry * cos(ROT_SPEED);
// 		old_planex = g->planex;
// 		g->planex = g->planex * cos(ROT_SPEED) - g->planey * sin(ROT_SPEED);
// 		g->planey = old_planex * sin(ROT_SPEED) + g->planey * cos(ROT_SPEED);
// 	}
// 	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
// 	{
// 		old_dirx = g->dirx;
// 		g->dirx = g->dirx * cos(-ROT_SPEED) - g->diry * sin(-ROT_SPEED);
// 		g->diry = old_dirx * sin(-ROT_SPEED) + g->diry * cos(-ROT_SPEED);
// 		old_planex = g->planex;
// 		g->planex = g->planex * cos(-ROT_SPEED) - g->planey * sin(-ROT_SPEED);
// 		g->planey = old_planex * sin(-ROT_SPEED) + g->planey * cos(-ROT_SPEED);
// 	}
// }

// /* window resize hook */
// static void	resize_hook(int32_t w, int32_t h, void *param)
// {
// 	t_game *g = param;
// 	g->width = w;
// 	g->height = h;
// 	render_scene(g);
// }

// /* loop hook */
// static void	game_loop(void *param)
// {
// 	t_game *g = param;
// 	move_player(g);
// 	render_scene(g);
// }

// /* ---------------------------------------------------- */

// int	main(void)
// {
// 	t_game g = {0};

// 	g.mlx = mlx_init(BASE_W, BASE_H, "Mini Cub3D - One Wall", true);
// 	if (!g.mlx)
// 		return (fprintf(stderr, "Failed to init MLX42\n"), EXIT_FAILURE);

// 	g.tex[0] = mlx_load_png("./textures/west.PNG");
// 	g.tex[1] = mlx_load_png("./textures/east.PNG");
// 	g.tex[2] = mlx_load_png("./textures/north.png");
// 	g.tex[3] = mlx_load_png("./textures/south.PNG");
// 	for (int i = 0; i < 4; ++i)
// 		if (!g.tex[i]) return (fprintf(stderr, "Missing texture %d\n", i), 1);

// 	g.width = BASE_W;
// 	g.height = BASE_H;
// 	g.px = 2.5;
// 	g.py = 2.0;
// 	g.dirx = -1;
// 	g.diry = 0;
// 	g.planex = 0;
// 	g.planey = FOV;

// 	g.img = mlx_new_image(g.mlx, g.width, g.height);
// 	render_scene(&g);

// 	mlx_resize_hook(g.mlx, resize_hook, &g);
// 	mlx_loop_hook(g.mlx, game_loop, &g);
// 	mlx_loop(g.mlx);

// 	for (int i = 0; i < 4; ++i)
// 		mlx_delete_texture(g.tex[i]);
// 	mlx_terminate(g.mlx);
// 	return (0);
// }