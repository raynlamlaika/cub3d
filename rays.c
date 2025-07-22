#include "cub.h"

#define TWO_PI 6.28318530718




void draw_ray_line(t_game *game, double x0, double y0, double x1, double y1, int color)
{
    double dx = x1 - x0;
    double dy = y1 - y0;
    double steps = fmax(fabs(dx), fabs(dy));
    double x_inc = dx / steps;
    double y_inc = dy / steps;

    double x = x0;
    double y = y0;

    for (int i = 0; i <= (int)steps; i++)
    {
        int px = (int)x;
        int py = (int)y;
        my_mlx_pixel_put(game, px, py, color);
        x += x_inc;
        y += y_inc;
    }
}


void draw_vertical_line(t_game *game, int x, double perp_dist, int side)
{
    // Avoid division by zero or very small distance
    if (perp_dist < 0.01)
        perp_dist = 0.01;

    // Calculate the projected wall height based on the distance
    int line_height = (int)((TILE_SIZE * (game->map_height * TILE_SIZE)) / perp_dist);

    // Calculate draw start and end positions
    int draw_start = -line_height / 2 + (game->map_height * TILE_SIZE) / 2;
    if (draw_start < 0)
        draw_start = 0;

    int draw_end = line_height / 2 + (game->map_height * TILE_SIZE) / 2;
    if (draw_end >= (game->map_height * TILE_SIZE))
        draw_end = (game->map_height * TILE_SIZE) - 1;

    // Choose a color (different shade for vertical/horizontal walls)
    int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;

    // Draw the vertical line
    for (int y = draw_start; y <= draw_end; y++)
    {
        my_mlx_pixel_put(game, x, y, color);
    }
}


void cast_ray(t_game *game, t_ray *ray, int ray_id)
{
    int step_x, step_y;
    double side_dist_x, side_dist_y;
    int hit = 0;
    int side; // holder for waht we did reatsh

    // Calculate step and initial sideDist
    if (ray->ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (ray->ray_x / TILE_SIZE - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (ray->map_x + 1.0 - ray->ray_x / TILE_SIZE) * ray->delta_dist_x;
    }

    if (ray->ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (ray->ray_y / TILE_SIZE - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (ray->map_y + 1.0 - ray->ray_y / TILE_SIZE) * ray->delta_dist_y;
    }


    // Perform DDA loop
    while (!hit)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += ray->delta_dist_x;
            ray->map_x += step_x;
            side = 0; // Vertical wall
        }
        else
        {
            side_dist_y += ray->delta_dist_y;
            ray->map_y += step_y;
            side = 1; // Horizontal wall
        }

        // Check if ray has hit a wall (map[y][x] == '1')
        if (game->map[ray->map_y][ray->map_x] == '1')
        {
            hit = 1;
        }
    }

    // Calculate perpendicular distance to the wall
    double perp_wall_dist;
    if (side == 0)
        perp_wall_dist = (ray->map_x * TILE_SIZE - ray->ray_x + (1 - step_x) * TILE_SIZE / 2) / ray->ray_dir_x;
    else
        perp_wall_dist = (ray->map_y * TILE_SIZE - ray->ray_y + (1 - step_y) * TILE_SIZE / 2) / ray->ray_dir_y;



    // Optional: Save result in ray struct
    ray->perp_wall_dist = perp_wall_dist;
    ray->side = side;

    // Calculate exact hit point (for drawing or texture mapping)
    ray->hit_x = ray->ray_x + ray->ray_dir_x * perp_wall_dist;
    ray->hit_y = ray->ray_y + ray->ray_dir_y * perp_wall_dist;

    // You can now use ray->hit_x and ray->hit_y to draw your ray line or walls
    double start_x = game->player.x * TILE_SIZE + TILE_SIZE / 2;
    double start_y = game->player.y * TILE_SIZE + TILE_SIZE / 2;

    // double end_x = ray->hit_x;
    // double end_y = ray->hit_y;
    // (void)ray_id;

    // printf("hit x and y (tiles):     (%f, %f)\n", ray->hit_x, ray->hit_y);
    printf("\n=========== RAYCAST DEBUG INFO ===========\n");
    printf("Player Position (pixels):   (%.2f, %.2f)\n", start_x, start_y);
    printf("Ray Start (pixels):         (%.2f, %.2f)\n", ray->ray_x, ray->ray_y);
    printf("Ray Direction:              (%.5f, %.5f)\n", ray->ray_dir_x, ray->ray_dir_y);
    printf("Tile Map Position:          (%d, %d)\n", ray->map_x, ray->map_y);
    printf("Step Direction:             (step_x = %d, step_y = %d)\n", (ray->ray_dir_x < 0 ? -1 : 1), (ray->ray_dir_y < 0 ? -1 : 1));
    printf("Delta Distances:            (dx = %.5f, dy = %.5f)\n", ray->delta_dist_x, ray->delta_dist_y);
    printf("Initial Side Distances:     (side_dx = %.5f, side_dy = %.5f)\n", side_dist_x, side_dist_y);
    printf("Wall Hit Side:              %s\n", ray->side == 0 ? "Vertical (X)" : "Horizontal (Y)");
    printf("Perpendicular Wall Dist:    %.5f\n", ray->perp_wall_dist);
    printf("Hit Position (pixels):      (%.2f, %.2f)\n", ray->hit_x, ray->hit_y);
    printf("==========================================\n\n");
    // sleep(1);
    // draw_ray_line(game, start_x, start_y, end_x, end_y, 0xFF0000);
    draw_vertical_line(game, ray_id, perp_wall_dist, side);
    
}

double normalize_angle(double angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}

// void ray_cast_all_dda(t_game *game)
// {
//     t_ray *holder;

//     holder = malloc (sizeof(t_ray));
//     holder->ray_x = game->player.x * TILE_SIZE + TILE_SIZE / 2;
//     holder->ray_y = game->player.y * TILE_SIZE + TILE_SIZE / 2;
//     int size = 2;
    
//     for (int dx = -size; dx <= size; dx++)
//     {
//         for (int dy = -size; dy <= size; dy++)
//         {
//             my_mlx_pixel_put(game, holder->ray_x + dx, holder->ray_y + dy, 0xFF0000); // red square
//         }
//     }

//     holder->ray_angle =  normalize_angle(game->angle);
//     holder->ray_dir_x = cos(holder->ray_angle);
//     holder->ray_dir_y = sin(holder->ray_angle);

//     holder->map_x = (int)(holder->ray_x / TILE_SIZE);
//     holder->map_y = (int)(holder->ray_y / TILE_SIZE);
//     if (fabs(holder->ray_dir_x) < 1e-6)
//         holder->delta_dist_x = 1e30;
//     else
//         holder->delta_dist_x = fabs(1 / holder->ray_dir_x);

//     if (fabs(holder->ray_dir_y) < 1e-6)
//         holder->delta_dist_y = 1e30;
//     else
//         holder->delta_dist_y = fabs(1 / holder->ray_dir_y);

//     printf("\n🔍 Ray Debug Info\n");
//     printf("------------------------\n");
//     printf("Player tile:         (%d, %d)\n", game->player.x * TILE_SIZE, game->player.y * TILE_SIZE);
//     printf("Ray Start (pixels):  (%f, %f)\n", holder->ray_x, holder->ray_y);
//     printf("Ray Angle (rad):     %f\n", holder->ray_angle);
//     printf("Ray Direction:       (%f, %f)\n", holder->ray_dir_x, holder->ray_dir_y);
//     printf("Delta Distances:     dx = %f | dy = %f\n", holder->delta_dist_x, holder->delta_dist_y);
//     printf("Map Pos (tiles):     (%d, %d)\n", holder->map_x, holder->map_y);
//     printf("------------------------\n");
//     // sleep(2);

//     cast_ray(game, holder);
// }



void ray_cast_all_dda(t_game *game)
{
    const int num_rays = 120;              // Number of rays cast across screen width
    const double fov = M_PI / 3;            // 60 degrees FOV
    double start_angle = normalize_angle(game->angle - fov / 2);
    double angle_step = fov / num_rays;

    for (int i = 0; i < num_rays; i++)
    {
        t_ray ray;
        ray.ray_x = game->player.x * TILE_SIZE + TILE_SIZE / 2;
        ray.ray_y = game->player.y * TILE_SIZE + TILE_SIZE / 2;

        ray.ray_angle = normalize_angle(start_angle + i * angle_step);
        ray.ray_dir_x = cos(ray.ray_angle);
        ray.ray_dir_y = sin(ray.ray_angle);

        ray.map_x = (int)(ray.ray_x / TILE_SIZE);
        ray.map_y = (int)(ray.ray_y / TILE_SIZE);

        ray.delta_dist_x = (fabs(ray.ray_dir_x) < 1e-6) ? 1e30 : fabs(1 / ray.ray_dir_x);
        ray.delta_dist_y = (fabs(ray.ray_dir_y) < 1e-6) ? 1e30 : fabs(1 / ray.ray_dir_y);

        cast_ray(game, &ray, i);

        // Optional: visualize rays on minimap or debug draw
        // my_mlx_pixel_put(game, ray.hit_x, ray.hit_y, 0xFF0000);
    }
}
