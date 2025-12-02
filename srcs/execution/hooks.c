#include "cub3d.h"

void	rotate_right(t_cub3d *cub)
{
	double	oldDirX = cub -> player.dirx;
	cub -> player.dirx = oldDirX * cos(ROT_SPEED) - cub -> player.diry * sin(ROT_SPEED);
	cub -> player.diry = oldDirX * sin(ROT_SPEED) + cub -> player.diry * cos(ROT_SPEED);

	cub -> player.plane_x = -cub ->player.diry * FOV;
	cub -> player.plane_y = cub -> player.dirx * FOV;
}

void	rotate_left(t_cub3d *cub)
{
	double	oldDirX = cub -> player.dirx;
	cub -> player.dirx = oldDirX * cos(ROT_SPEED) + cub -> player.diry * sin(ROT_SPEED);
	cub -> player.diry = -oldDirX * sin(ROT_SPEED) + cub -> player.diry * cos(ROT_SPEED);

	cub -> player.plane_x = -cub ->player.diry * FOV;
	cub -> player.plane_y = cub -> player.dirx * FOV;
}

void move_forward(t_cub3d *cub)
{
	double	new_px;
	double	new_py;

	if (mlx_is_key_down(cub -> mlx, MLX_KEY_LEFT_SHIFT))
		cub -> player.move_speed = SPRINT_SPEED;
	else
		cub -> player.move_speed = MOVE_SPEED;
	new_px = cub -> player.px + cub -> player.dirx * cub -> player.move_speed;
	new_py = cub -> player.py + cub -> player.diry * cub -> player.move_speed;
	if (cub -> map.grid[(int)(cub -> player.py)][(int)(new_px)] != '1')
		cub -> player.px = new_px;
	if (cub -> map.grid[(int)(new_py)][(int)(cub -> player.px)] != '1')
		cub -> player.py = new_py;
}

void move_backward(t_cub3d *cub)
{
	double	new_px;
	double	new_py;

	if (mlx_is_key_down(cub -> mlx, MLX_KEY_LEFT_SHIFT))
		cub -> player.move_speed = SPRINT_SPEED;
	else
		cub -> player.move_speed = MOVE_SPEED;
	new_px = cub -> player.px - cub -> player.dirx * cub -> player.move_speed;
	new_py = cub -> player.py - cub -> player.diry * cub -> player.move_speed;
	if (cub -> map.grid[(int)(cub -> player.py)][(int)(new_px)] != '1')
		cub -> player.px = new_px;
	if (cub -> map.grid[(int)(new_py)][(int)(cub -> player.px)] != '1')
		cub -> player.py = new_py;
}

void move_right(t_cub3d *cub)
{
	double	new_px;
	double	new_py;

	if (mlx_is_key_down(cub -> mlx, MLX_KEY_LEFT_SHIFT))
		cub -> player.move_speed = SPRINT_SPEED;
	else
		cub -> player.move_speed = MOVE_SPEED;
	new_px = cub -> player.px + -cub -> player.diry * cub -> player.move_speed;
	new_py = cub -> player.py + cub -> player.dirx * cub -> player.move_speed;
	if (cub -> map.grid[(int)(cub -> player.py)][(int)(new_px)] != '1')
		cub -> player.px = new_px;
	if (cub -> map.grid[(int)(new_py)][(int)(cub -> player.px)] != '1')
		cub -> player.py = new_py;
}

void move_left(t_cub3d *cub)
{
	double	new_px;
	double	new_py;

	if (mlx_is_key_down(cub -> mlx, MLX_KEY_LEFT_SHIFT))
		cub -> player.move_speed = SPRINT_SPEED;
	else
		cub -> player.move_speed = MOVE_SPEED;
	new_px = cub -> player.px + cub -> player.diry * cub -> player.move_speed;
	new_py = cub -> player.py + -cub -> player.dirx * cub -> player.move_speed;
	if (cub -> map.grid[(int)(cub -> player.py)][(int)(new_px)] != '1')
		cub -> player.px = new_px;
	if (cub -> map.grid[(int)(new_py)][(int)(cub -> player.px)] != '1')
		cub -> player.py = new_py;
}