#include "cub.h"

int	main(int ac, char **av)
{
	t_game	*game;
	int		fd;
	char	*line;

	check_argument(ac, av);

	game = malloc(sizeof(t_game));
	if (!game)
	{
		perror("Error\n<----!Memory allocation failed---->");
		exit(1);
	}
	init_game_struct(game);

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error\n<----!Can't open file---->");
		exit(1);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		// if (!is_empty_line(line))
			parse_line(game, line);
		// printf ("%s", line);
		free(line);
	}
	close(fd);

	// Next steps would be:
	finalize_map(game);
	print_map(game->map);
	validate_map(game);




	init_game(game);
	mlx_hook(game->helper->win, 17, 0, close_window, game);
	mlx_hook(game->helper->win, 2, 1, bottoms, game);
	mlx_loop_hook(game->helper->mlx,&render_map, game);
	mlx_loop(game->helper->mlx);

	return (0);
}
