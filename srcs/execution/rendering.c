#include "cub3d.h"

uint32_t apply_fog(uint32_t color, double distance)
{
    // 1. Calculate brightness factor (inverse of distance)
    // The number '5.0' controls how far the "light" reaches.
    // Try changing 5.0 to 10.0 for brighter, or 2.0 for darker scenes.
    double brightness = 3.0 / distance; 
    
    // Clamp brightness between 0.0 (black) and 1.0 (full color)
    if (brightness > 1.0) brightness = 1.0;
    if (brightness < 0.0) brightness = 0.0;

    // 2. Extract RGBA channels
    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8) & 0xFF;
    uint8_t a = color & 0xFF;

    // 3. Dim the RGB channels
    r = (uint8_t)(r * brightness);
    g = (uint8_t)(g * brightness);
    b = (uint8_t)(b * brightness);

    // 4. Recombine and return
    return (r << 24) | (g << 16) | (b << 8) | a;
}

void	render_floor_ceil(mlx_image_t *img, t_assets *ass)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < WIN_HEIGHT / 2)
	{
		j = 0;
		while (j < WIN_WIDTH )
		{
			mlx_put_pixel(img, j, i, ass -> c_color);
			j++;
		}
		i++;
	}
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH )
		{
			mlx_put_pixel(img, j, i, ass -> f_color);
			j++;
		}
		i++;
	}
}

static uint32_t get_texture_pixel(mlx_texture_t *tex, int x, int y, double wall_dist)
{
    // 1. Safety Check: If coordinates are out of bounds, return Black or Error color
    if (x < 0 || x >= (int)tex->width || y < 0 || y >= (int)tex->height)
        return 0x000000FF; 

    // 2. Calculate the index in the 1D pixel array
    // Each pixel has 4 bytes (Red, Green, Blue, Alpha)
    // Formula: (Row * Width + Column) * 4
    int index = (y * tex->width + x) * 4;
    
    // 3. Extract the bytes (MLX42 stores them as RGBA)
    uint8_t r = tex->pixels[index];     // Red
    uint8_t g = tex->pixels[index + 1]; // Green
    uint8_t b = tex->pixels[index + 2]; // Blue
    uint8_t a = tex->pixels[index + 3]; // Alpha

	uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
    // 4. Combine them into one 32-bit integer (0xRRGGBBAA)
    // We shift Red to the far left, then Green, then Blue, then Alpha at the end.
    return apply_fog(color, wall_dist);
}
void	render_rays(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		// Calculate Ray dir and map pixels to camera_x

		cub -> ray.camera_x = (2 * i / (double)WIN_WIDTH) - 1;
		cub -> ray.raydirx = cub -> player.dirx + (cub -> player.planex * cub->ray.camera_x);
		cub -> ray.raydiry = cub -> player.diry + (cub -> player.planey * cub->ray.camera_x);
		cub -> ray.mapx = (int)cub -> player.px;
		cub -> ray.mapy = (int)cub -> player.py;

		calculate_dist(&cub -> ray, &cub -> player);
		perform_dda(&cub -> ray, &cub -> map);
		get_texture(&cub -> ray, &cub -> render, &cub -> ass);
		// Calculate hit point
		double wallX;
		if (cub -> ray.side == WE)
			wallX = cub -> player.py + cub -> ray.wall_dist * cub -> ray.raydiry;
		else
			wallX = cub -> player.px + cub -> ray.wall_dist * cub -> ray.raydirx;
		wallX -= floor(wallX);

		double texX;
		texX = (int)(wallX * (double)cub -> render.tex -> width);
		// 2. Fix the Mirror Effect
		// If hitting a side where coordinates run backwards, flip x.
		if ((cub->ray.side == WE && cub->ray.raydirx > 0))// East Face
			texX = cub -> render.tex -> width - texX - 1;
		if (cub -> ray.side == NS && cub -> ray.raydiry < 0)
			texX = cub -> render.tex -> width - texX - 1;
		double step = 1.0 * cub -> render.tex -> height / cub -> render.wall_height;
		double texPos = (cub -> render.draw_start - WIN_HEIGHT / 2 + cub -> render.wall_height / 2) * step;

		// 5. The Drawing Loop
		int y = cub -> render.draw_start;
		while (y <= cub -> render.draw_end)
		{
    		// Get the integer Y position on the texture
    		int texY = (int)texPos & (cub -> render.tex->height - 1); // The & prevents overflow errors
    		texPos += step;

 		   // Get the color from the texture at [texY][texX]
    		uint32_t color = get_texture_pixel(cub -> render.tex, texX, texY, cub -> ray.wall_dist);

   			 // Draw it!
   			 mlx_put_pixel(cub->img, i, y, color);
    		y++;
		}
		i++;
	}
}
