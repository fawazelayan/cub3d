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

// void	render_floor_ceil(t_cub3d *cub)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (i < WIN_HEIGHT / 2)
// 	{
// 		j = 0;
// 		while (j < WIN_WIDTH )
// 		{
// 			mlx_put_pixel(cub -> img, j, i, cub -> ass.c_color);
// 			j++;
// 		}
// 		i++;
// 	}
// 	while (i < WIN_HEIGHT)
// 	{
// 		j = 0;
// 		while (j < WIN_WIDTH )
// 		{
// 			mlx_put_pixel(cub -> img, j, i, cub -> ass.f_color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void render_floor_ceil(t_cub3d *cub)
{
    int y;
    int x;

    // --- CEILING (Top Half) ---
    y = 0;
    while (y < WIN_HEIGHT / 2)
    {
        // 1. Calculate distance based on how "high" we are
        // (WIN_HEIGHT / 2) - y  is the distance from the horizon line
        double dist = (WIN_HEIGHT / 2.0) / ((WIN_HEIGHT / 2.0) - y);
        
        // 2. Calculate the color ONCE for the whole row
        uint32_t foggy_color = apply_fog(cub->ass.c_color, dist);

        // 3. Draw the row
        x = 0;
        while (x < WIN_WIDTH)
        {
            mlx_put_pixel(cub->img, x, y, foggy_color);
            x++;
        }
        y++;
    }

    // --- FLOOR (Bottom Half) ---
    y = WIN_HEIGHT / 2;
    while (y < WIN_HEIGHT)
    {
        // 1. Calculate distance based on how "low" we are
        // y - (WIN_HEIGHT / 2) is the distance from the horizon line
        double row_pos = y - (WIN_HEIGHT / 2.0);
        
        // Avoid division by zero at the exact center line
        if (row_pos == 0) row_pos = 1.0; 
        
        double dist = (WIN_HEIGHT / 2.0) / row_pos;

        // 2. Calculate the color ONCE
        uint32_t foggy_color = apply_fog(cub->ass.f_color, dist);

        // 3. Draw the row
        x = 0;
        while (x < WIN_WIDTH)
        {
            mlx_put_pixel(cub->img, x, y, foggy_color);
            x++;
        }
        y++;
    }
}

static uint32_t get_texture_pixel(mlx_texture_t *tex, int x, int y, double wallDist)
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
    return apply_fog(color, wallDist);
}
void	render_rays(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		// Calculate Ray dir and map pixels to camera_x

		cub -> ray.camera_x = (2 * i / (double)WIN_WIDTH) - 1;
		cub -> ray.ray_x = cub -> player.dirx + (cub -> player.plane_x * cub->ray.camera_x);
		cub -> ray.ray_y = cub -> player.diry + (cub -> player.plane_y * cub->ray.camera_x);
		cub -> ray.map_x = (int)cub -> player.px;
		cub -> ray.map_y = (int)cub -> player.py;

		// Calculate DELTA DIST
		if (!cub -> ray.ray_x)
			cub -> ray.deltaX = 1e30;
		else
			cub -> ray.deltaX = fabs(1/cub -> ray.ray_x);
		if (!cub -> ray.ray_y)
			cub -> ray.deltaY = 1e30;
		else
			cub -> ray.deltaY = fabs(1/cub -> ray.ray_y);

		// Calculate steps and side Dist
		if (cub -> ray.ray_x < 0)
		{
			cub -> ray.stepX = -1;
			cub -> ray.sideX = (cub -> player.px - cub -> ray.map_x) * cub -> ray.deltaX;
		}
		else
		{
			cub -> ray.stepX = 1;
			cub -> ray.sideX = (cub -> ray.map_x + 1 - cub -> player.px) * cub -> ray.deltaX;
		}
		if (cub -> ray.ray_y < 0)
		{
			cub -> ray.stepY = -1;
			cub -> ray.sideY = (cub -> player.py - cub -> ray.map_y) * cub -> ray.deltaY;
		}
		else
		{
			cub -> ray.stepY = 1;
			cub -> ray.sideY = (cub -> ray.map_y + 1 - cub -> player.py) * cub -> ray.deltaY;
		}

		// Increament steps till a wall hit
		cub -> ray.hit = false;
		while (!cub -> ray.hit)
		{
			if (cub -> ray.sideX < cub -> ray.sideY)
			{
				cub -> ray.sideX += cub -> ray.deltaX;
				cub -> ray.map_x += cub -> ray.stepX;
				cub -> ray.side = WE;
			}
			else
			{
				cub -> ray.sideY += cub -> ray.deltaY;
				cub -> ray.map_y += cub -> ray.stepY;
				cub -> ray.side = NS;
			}
			if (cub -> map.grid[cub -> ray.map_y][cub -> ray.map_x] == '1')
				cub -> ray.hit = true;
		}

		// Calculate wall distance
		if (cub -> ray.side == WE)
			cub -> ray.wallDist = cub -> ray.sideX - cub -> ray.deltaX;
		else
			cub -> ray.wallDist = cub -> ray.sideY - cub -> ray.deltaY;

		// Calculate wall height (how many pixels)
		int wallHeight = (int)(WIN_HEIGHT/ cub -> ray.wallDist);

		// Calculate draw start and end for the wall
		int	drawStart = WIN_HEIGHT / 2 - wallHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = WIN_HEIGHT / 2 + wallHeight / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		// Load the right texture for dir
		mlx_texture_t *tex;
		if (cub -> ray.side == WE)
		{
			if (cub -> ray.ray_x < 0)
				tex = cub -> ass.ea_tex;
			else
				tex = cub -> ass.we_tex;
		}
		else
		{
			if (cub -> ray.ray_y < 0)
				tex = cub -> ass.so_tex;
			else
				tex = cub -> ass.no_tex;
		}

		// Calculate hit point
		double wallX;
		if (cub -> ray.side == WE)
			wallX = cub -> player.py + cub -> ray.wallDist * cub -> ray.ray_y;
		else
			wallX = cub -> player.px + cub -> ray.wallDist * cub -> ray.ray_x;
		wallX -= floor(wallX);

		double texX;
		texX = (int)(wallX * (double)tex -> width);
		// 2. Fix the Mirror Effect
		// If hitting a side where coordinates run backwards, flip x.
		if ((cub->ray.side == WE && cub->ray.ray_x > 0))// East Face
			texX = tex -> width - texX - 1;
		if (cub -> ray.side == NS && cub -> ray.ray_y < 0)
			texX = tex -> width - texX - 1;
		double step = 1.0 * tex -> height / wallHeight;
		double texPos = (drawStart - WIN_HEIGHT / 2 + wallHeight / 2) * step;

		// 5. The Drawing Loop
		int y = drawStart;
		while (y <= drawEnd)
		{
    		// Get the integer Y position on the texture
    		int texY = (int)texPos & (tex->height - 1); // The & prevents overflow errors
    		texPos += step;

 		   // Get the color from the texture at [texY][texX]
    		uint32_t color = get_texture_pixel(tex, texX, texY, cub -> ray.wallDist);

   			 // Draw it!
   			 mlx_put_pixel(cub->img, i, y, color);
    		y++;
		}
		i++;
	}
}
