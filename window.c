#include "cub.h"

int	init_window(t_screen *window)
{
	if (!window)
		exit(12);
	window->init = mlx_init();

	if (!window->init)
		return (write(2, "the init of the mlx are failed\n", 32), exit(1), 0);
	window->wind = mlx_new_window(window->init, SCREEN_WIDTH, SCREEN_HEIGHT, "CUUUB");
	if (!window->wind)
		return (write(2, "window of the mlx are failed\n", 29), \
				free(window->init), exit(1), 0);
	window->img = mlx_new_image(window->init, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!window->img)
	{
		write(2, "faild in the img creation\n", 26);
		free(window->init);
		return (exit(1), 0);
	}
	window->addr = mlx_get_data_addr(window->img, \
		&window->bits_for_pixel, &window->line_length, &window->endian);
	if (!window->addr)
		exit(1);
	return (1);
}


