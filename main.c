#include "cub.h"

void	is_valid_texture(t_game *game)
{
	if (game->no != 1 || game->so != 1 || game->we != 1 || game->ea != 1 || game->f != 1 || game->c != 1)
	{
		printf("[%d], [%d], [%d], [%d], [%d], [%d], \n", game->no, game->so, game->we, game->ea, game->f, game->c);
		print_error("Invalid texture");
	}
}

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
		if (!is_empty_line(line))
			parse_line(game, line);
		// printf ("%s", line);
		free(line);
	}
	close(fd);

	// Next steps would be:
	is_valid_texture(game);
	finalize_map(game);
	print_map(game->map);
	validate_map(game);
	// and parse the map in file map.cub in function validate_map
	return (0);
}
