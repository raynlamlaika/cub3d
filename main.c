
#include "cub.h"
#define WALLSIZE 70

double normalize_angle(double angle)
{
	while (angle < 0)
		angle += TWO_PI;
	while (angle >= TWO_PI)
		angle -= TWO_PI;
	return angle;
}


int cast_s_ray(t_player *player_info, double angle)
{
	double ray_x;
	double ray_y;
	double step;

	ray_x = player_info->x_axes;
	ray_y = player_info->y_axes;
	step = player_info->step_size;
	while (1)
	{
		ray_x += cos(angle) * step;
		ray_y += sin(angle) * step;
		int map_x = (int)ray_x;
		int map_y = (int)ray_y;
		if (player_info->map[map_y] == NULL || map_x < 0 || map_y < 0)
			break;
		if (player_info->map[map_y][map_x] == '1') // the walls checks
		{
			printf("Ray hit wall at: tile (%d, %d), position (%.2f, %.2f)\n", map_x, map_y, ray_x, ray_y);
			break;
		}
	}
	return (1);
}

void cast_all_rays(t_player *player)
{
	int rays;
	int i;
	double ray_angle;

	i = 0;
	rays = SCREEN_WIDTH;
	while (i < rays)
	{
		ray_angle = player->angle
						 - (FOV / 2)                          // start left
						 + ((double)i / rays) * FOV;      // step across FOV

		ray_angle = normalize_angle(ray_angle);  // keep between 0 and 2π
		cast_s_ray(player, ray_angle);
		i++;
	}
}


int	clearr(t_screen *frac)
{
	if (frac->init && frac->wind)
		mlx_destroy_window(frac->init, frac->wind);
	exit(1);
	return (1);
}
int	mouse_hook_mandel(int button, int x, int y, t_screen *frac)
{
	double	mouse_real;
	double	mouse_imag;

	return (0);
}
#define TAIL_SIZE 60


int drawing(int i, int y ,int col, t_screen* window)
{
	int px;
	int py;

	py = 0;
	px = 0;
	while (px < TAIL_SIZE)
	{
		py  = 0;
		while (py < TAIL_SIZE)
		{
			mlx_pixel_put(window->init, window->wind, y * TAIL_SIZE + py, i * TAIL_SIZE + px, col);
			py++;
		}
		px++;
	}
	return (0);
}

void draw_map(t_screen *window, char **map)
{
	int	i;
	int	y;
	int	col;

	i = 0;
	y = 0;
	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			if (map[i][y] == '0')
				col = 0xFFFFFF;
			else if (map[i][y] == 'P')
				col = 0xFFF000;
			else if (map[i][y] == '1')
				col = 0x000000;
			else
				col = 0x00FF00;
			drawing( i,y,col, window);
			y++;
		}
		i++;
	}
}

void draw_player(t_screen *win)
{
	int px, py;

	px = 0;
	while (px < 5)
	{
		py = 0;
		while (py < 5)
		{
			mlx_pixel_put(win->init, win->wind, win->player->x_axes + px, win->player->y_axes + py, 0xFF0000);
			py++;
		}
		px++;
	}
}

int	key_hook(int keycode, t_screen *win)
{
	int step = 10;

	if (!win || !win->player)
		return (1);
	if (keycode == 53) // ESC
		exit(0);
	else if (keycode == 13) // W key
		win->player->y_axes -= step;
	else if (keycode == 1) // S key
		win->player->y_axes += step;
	else if (keycode == 0) // A key
		win->player->x_axes -= step;
	else if (keycode == 2) // D key
		win->player->x_axes += step;

	mlx_clear_window(win->init, win->wind);
	draw_map(win, win->player->map);
	draw_player(win);

	return (0);
}

void find_player_position(t_player *player)
{
	int i = 0;
	int j;

	while (player->map[i])
	{
		
		j = 0;
		while (player->map[i][j])
		{
			if (player->map[i][j] == 'P')
			{
				
				player->x_axes = j * TAIL_SIZE + TAIL_SIZE / 2;
				player->y_axes = i * TAIL_SIZE + TAIL_SIZE / 2;
				player->angle = 0;
				
				player->step_size = 5.0;
				player->map[i][j] = '0'; // Replace 'P' with '0'
				
				return;
			}
			j++;
		}
		i++;
	}
}

int raycasting(t_player *start, t_screen *window)
{
	init_window(window);

	draw_map(window, start->map);


	mlx_key_hook(window->wind, key_hook, window);
	mlx_mouse_hook(window->wind, mouse_hook_mandel, window);
	mlx_hook(window->wind, 17, 0, &clearr, window);
	mlx_loop(window->init);
	mlx_destroy_image(window->init, window->img);
	mlx_destroy_window(window->init, window->wind);
	return (0);
}



int main()
{
	t_player	*start;
    t_screen	*window;
	window = malloc(sizeof(t_screen));
    start = malloc(sizeof(t_player));
	start->window = window;
	window->player = start;
	char *temp_map[] = {
	"1111111111",
	"1000000001",
	"1011000001",
	"1P01000001",
	"1000000001",
	"1111111111",
	NULL
	};

	int row_count = 0;
	while (temp_map[row_count])
		row_count++;

	start->map = malloc(sizeof(char *) * (row_count + 1));
	for (int i = 0; i < row_count; i++)
		start->map[i] = strdup(temp_map[i]);  // allocates new writable copy
	start->map[row_count] = NULL;

	write(2,"helo\n",5);
	find_player_position(start);

	raycasting(start, window);
	free(start);
	free(window);
	return 1;
}




