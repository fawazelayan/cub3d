#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "MLX42.h"

#define WIDTH 1024
#define HEIGHT 768
#define ROT_SPEED 0.05
#define MOVE_SPEED 0.05

// MAP DIMENSIONS
#define MAP_W 24
#define MAP_H 24

// --- Global Map (Using characters 1, 0, N, S, E, W) ---
// Note: We use char arrays so we can modify the map (remove the player char) if needed.
char worldMap[MAP_H][MAP_W + 1] = {
    "111111111111111111111111",
    "100000000000000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "100000111110000000000001",
    "100000100010000000000001",
    "100000100010000000000001",
    "100000100010000000000001",
    "100000110110000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "111111111000000000000001",
    "100000001000000000000001",
    "100000001000000000000001",
    "100000001000000000000001",
    "100000001000000000000001",
    "100000000000000000000001",
    "1000000000000W0000000001", // <--- PLAYER SPAWN (W = West)
    "111111111111111111111111"
};

typedef struct s_game {
    mlx_t           *mlx;
    mlx_image_t     *img;
    mlx_texture_t   *tex_n;
    mlx_texture_t   *tex_s;
    mlx_texture_t   *tex_e;
    mlx_texture_t   *tex_w;
    
    // Player vars
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;
} t_game;

// Helper: Get pixel color from texture
uint32_t get_tex_color(mlx_texture_t *tex, int x, int y) {
    if (x < 0 || x >= (int)tex->width || y < 0 || y >= (int)tex->height) return 0x000000FF;
    int idx = (y * tex->width + x) * 4;
    return (tex->pixels[idx] << 24) | (tex->pixels[idx+1] << 16) | (tex->pixels[idx+2] << 8) | tex->pixels[idx+3];
}

// Helper: Check if a map position is walkable (0 or the spawn letters)
int is_walkable(int x, int y) {
    char c = worldMap[x][y];
    return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void hook(void *param) {
    t_game *g = (t_game *)param;

    // --- Movement ---
    // Note: In this map, X is the row (vertical in code), Y is col (horizontal in code)
    if (mlx_is_key_down(g->mlx, MLX_KEY_W)) {
        if(is_walkable((int)(g->posX + g->dirX * MOVE_SPEED), (int)g->posY)) g->posX += g->dirX * MOVE_SPEED;
        if(is_walkable((int)(g->posX), (int)(g->posY + g->dirY * MOVE_SPEED))) g->posY += g->dirY * MOVE_SPEED;
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_S)) {
        if(is_walkable((int)(g->posX - g->dirX * MOVE_SPEED), (int)g->posY)) g->posX -= g->dirX * MOVE_SPEED;
        if(is_walkable((int)(g->posX), (int)(g->posY - g->dirY * MOVE_SPEED))) g->posY -= g->dirY * MOVE_SPEED;
    }
    
    // --- Rotation ---
    if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT)) {
        double oldDirX = g->dirX;
        g->dirX = g->dirX * cos(-ROT_SPEED) - g->dirY * sin(-ROT_SPEED);
        g->dirY = oldDirX * sin(-ROT_SPEED) + g->dirY * cos(-ROT_SPEED);
        double oldPlaneX = g->planeX;
        g->planeX = g->planeX * cos(-ROT_SPEED) - g->planeY * sin(-ROT_SPEED);
        g->planeY = oldPlaneX * sin(-ROT_SPEED) + g->planeY * cos(-ROT_SPEED);
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT)) {
        double oldDirX = g->dirX;
        g->dirX = g->dirX * cos(ROT_SPEED) - g->dirY * sin(ROT_SPEED);
        g->dirY = oldDirX * sin(ROT_SPEED) + g->dirY * cos(ROT_SPEED);
        double oldPlaneX = g->planeX;
        g->planeX = g->planeX * cos(ROT_SPEED) - g->planeY * sin(ROT_SPEED);
        g->planeY = oldPlaneX * sin(ROT_SPEED) + g->planeY * cos(ROT_SPEED);
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE)) mlx_close_window(g->mlx);

    // --- Draw Floor/Ceiling ---
    for(int y=0; y<HEIGHT; y++)
        for(int x=0; x<WIDTH; x++)
            mlx_put_pixel(g->img, x, y, (y < HEIGHT/2) ? 0x333333FF : 0x111111FF);

    // --- Raycasting ---
    for(int x = 0; x < WIDTH; x++) {
        double cameraX = 2 * x / (double)WIDTH - 1;
        double rayDirX = g->dirX + g->planeX * cameraX;
        double rayDirY = g->dirY + g->planeY * cameraX;

        int mapX = (int)g->posX;
        int mapY = (int)g->posY;

        double sideDistX, sideDistY;
        double dltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double dltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist;

        int stepx, stepy;
        int hit = 0, side;

        if (rayDirX < 0) { stepx = -1; sideDistX = (g->posX - mapX) * dltaDistX; }
        else { stepx = 1; sideDistX = (mapX + 1.0 - g->posX) * dltaDistX; }
        if (rayDirY < 0) { stepy = -1; sideDistY = (g->posY - mapY) * dltaDistY; }
        else { stepy = 1; sideDistY = (mapY + 1.0 - g->posY) * dltaDistY; }

        while (hit == 0) {
            if (sideDistX < sideDistY) { sideDistX += dltaDistX; mapX += stepx; side = 0; }
            else { sideDistY += dltaDistY; mapY += stepy; side = 1; }
            // Check for wall '1'
            if (worldMap[mapX][mapY] == '1') hit = 1;
        }

        if (side == 0) perpWallDist = (sideDistX - dltaDistX);
        else perpWallDist = (sideDistY - dltaDistY);

        int lineHeight = (int)(HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if(drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

        // Texture Calc
        mlx_texture_t *tex;
        if (side == 0 && rayDirX > 0) tex = g->tex_s;      // Using S for "bottom" side in array logic
        else if (side == 0 && rayDirX < 0) tex = g->tex_n; // Using N for "top" side
        else if (side == 1 && rayDirY > 0) tex = g->tex_e;
        else tex = g->tex_w;

        double wallX;
        if (side == 0) wallX = g->posY + perpWallDist * rayDirY;
        else wallX = g->posX + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        int texX = (int)(wallX * (double)tex->width);
        if((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0)) texX = tex->width - texX - 1;

        double step = 1.0 * tex->height / lineHeight;
        double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

        for(int y = drawStart; y < drawEnd; y++) {
            int texY = (int)texPos & (tex->height - 1);
            texPos += step;
            uint32_t color = get_tex_color(tex, texX, texY);
            mlx_put_pixel(g->img, x, y, color);
        }
    }
}

void init_player(t_game *g) {
    g->posX = -1; // Flag to check if found
    for (int x = 0; x < MAP_H; x++) {
        for (int y = 0; y < MAP_W; y++) {
            char c = worldMap[x][y];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W') {
                g->posX = x + 0.5;
                g->posY = y + 0.5;
                
                // Vectors setup based on direction
                // Note: Standard Wolf3D: N = (-1, 0), S = (1, 0), E = (0, 1), W = (0, -1) relative to map array
                if (c == 'N') { g->dirX = -1; g->dirY = 0; g->planeX = 0; g->planeY = 0.66; }
                if (c == 'S') { g->dirX = 1; g->dirY = 0; g->planeX = 0; g->planeY = -0.66; }
                if (c == 'E') { g->dirX = 0; g->dirY = 1; g->planeX = 0.66; g->planeY = 0; }
                if (c == 'W') { g->dirX = 0; g->dirY = -1; g->planeX = -0.66; g->planeY = 0; }
                return; // Found player, stop searching
            }
        }
    }
    if (g->posX == -1) { printf("Error: No Spawn Point (N/S/E/W) found in map.\n"); exit(1); }
}

int main(void) {
    t_game game;

    game.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D Char Map", true);
    if (!game.mlx) return 1;

    // Load Textures
    game.tex_n = mlx_load_png("./textures/north.png");
    game.tex_s = mlx_load_png("./textures/south.png");
    game.tex_e = mlx_load_png("./textures/east.png");
    game.tex_w = mlx_load_png("./textures/west.png");

    if (!game.tex_n || !game.tex_s || !game.tex_e || !game.tex_w) {
        printf("Error: Missing PNG textures.\n");
        return 1;
    }

    game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
    mlx_image_to_window(game.mlx, game.img, 0, 0);

    init_player(&game); // Find N, S, E, or W in the map

    mlx_loop_hook(game.mlx, hook, &game);
    mlx_loop(game.mlx);
    
    mlx_terminate(game.mlx);
    return 0;
}