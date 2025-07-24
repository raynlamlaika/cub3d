#include "cub.h"

#define TWO_PI 6.28318530718

void	draw_vertical_line(t_game *game, int x, int start, int end, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH)
		return;
	if (start < 0)
		start = 0;
	if (end >= SCREEN_HEIGHT)
		end = SCREEN_HEIGHT - 1;

	char	*pixel;
	int		y;

	y = start;
	while (y <= end)
	{
		pixel = game->helper->addr + (y * game->helper->line_len + x * (game->helper->bpp / 8));
		*(unsigned int *)pixel = color;
        // my_mlx_pixel_put(game,x, y,color);
		y++;
	}
}


double cast_ray(t_game *game, t_ray *ray, int ray_id)
{
    int step_x, step_y;
    double side_dist_x, side_dist_y;
    int hit = 0;
    int side;
    (void)ray_id;
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
    // double start_x = game->player.x * TILE_SIZE + TILE_SIZE / 2;
    // double start_y = game->player.y * TILE_SIZE + TILE_SIZE / 2;

    // double end_x = ray->hit_x;
    // double end_y = ray->hit_y;
    // (void)ray_id;

    // printf("hit x and y (tiles):     (%f, %f)\n", ray->hit_x, ray->hit_y);
    // printf("\n=========== RAYCAST DEBUG INFO ===========\n");
    // printf("Player Position (pixels):   (%.2f, %.2f)\n", start_x, start_y);
    // printf("Ray Start (pixels):         (%.2f, %.2f)\n", ray->ray_x, ray->ray_y);
    // printf("Ray Direction:              (%.5f, %.5f)\n", ray->ray_dir_x, ray->ray_dir_y);
    // printf("Tile Map Position:          (%d, %d)\n", ray->map_x, ray->map_y);
    // printf("Step Direction:             (step_x = %d, step_y = %d)\n", (ray->ray_dir_x < 0 ? -1 : 1), (ray->ray_dir_y < 0 ? -1 : 1));
    // printf("Delta Distances:            (dx = %.5f, dy = %.5f)\n", ray->delta_dist_x, ray->delta_dist_y);
    // printf("Initial Side Distances:     (side_dx = %.5f, side_dy = %.5f)\n", side_dist_x, side_dist_y);
    // printf("Wall Hit Side:              %s\n", ray->side == 0 ? "Vertical (X)" : "Horizontal (Y)");
    // printf("Perpendicular Wall Dist:    %.5f\n", ray->perp_wall_dist);
    // printf("Hit Position (pixels):      (%.2f, %.2f)\n", ray->hit_x, ray->hit_y);
    // printf("==========================================\n\n");
    // sleep(1);
    // draw_ray_line(game, start_x, start_y, end_x, end_y, 0xFF0000);
    // draw_vertical_line(game, ray_id, perp_wall_dist, side);
    
    return perp_wall_dist;
}

double normalize_angle(double angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}








void    the_3dview(t_game *game)
{
    double fov;
    int     i_loop;
    t_ray   ray;
    double angle_step;
    double start_angle;

    i_loop = 0;
    fov = M_PI / 3.0; // witc is the view 60
    angle_step = fov / (double)SCREEN_WIDTH;// to represent every dgree one oriziotal line
    start_angle = normalize_angle(game->angle - fov / 2);
    printf("[");
    while(i_loop <= SCREEN_WIDTH)
    {
        // prepare_vars(ray);
        ray.ray_angle = normalize_angle(start_angle + i_loop * angle_step);
        ray.ray_x  =  game->player.x * TILE_SIZE + TILE_SIZE / 2;
        ray.ray_y  =  game->player.y * TILE_SIZE + TILE_SIZE / 2;
        ray.ray_dir_x = cos(ray.ray_angle);
        ray.ray_dir_y = sin(ray.ray_angle);
        ray.map_x = (int)(ray.ray_x / TILE_SIZE);
        ray.map_y = (int)(ray.ray_y / TILE_SIZE);
        ray.delta_dist_x = (fabs(ray.ray_dir_x) < 1e-6) ? 1e30 : fabs(1 / ray.ray_dir_x);
        ray.delta_dist_y = (fabs(ray.ray_dir_y) < 1e-6) ? 1e30 : fabs(1 / ray.ray_dir_y);
        ray.ray_angle = normalize_angle(start_angle + i_loop * angle_step);
        double distance = cast_ray(game, &ray, i_loop);
        printf("destence:%f,\t", distance);
        double corrected_distance = distance * cos(ray.ray_angle - game->angle);

        int line_height = (int)(TILE_SIZE * SCREEN_HEIGHT / corrected_distance);
        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;

        if (draw_start < 0) draw_start = 0;
        if (draw_end >= SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT - 1;

        int color = (ray.side == 1) ? 0xAAAAAA : 0xFFFFFFd;
        draw_vertical_line(game, i_loop, draw_start, draw_end, color);
        i_loop++;
    }
    printf("]\n");



}
